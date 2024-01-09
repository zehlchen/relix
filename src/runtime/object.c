/*
 * RELIX ReScript, Copyright (C) 2024 Chase Zehl O'Byrne
 *  <mail: zehl@live.com> http://zehlchen.com/
 *
 * This file is part of RELIX.
 *
 * RELIX is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * RELIX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RELIX; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "runtime.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "memory.h"

Object* Object_new(Object* proto)
{
  Object* new = rx_malloc(sizeof(Object));
  new->proto  = proto;
  new->slots  = 0;
  return new;
}

Object* Object_delete(Object* self)
{
  if (self->slots)
    rx_free(self->slots);
  rx_free(self);
  return Qnil;
}

Object* Object_setSlot(Object* self, Object* key, Object* value)
{
  if (!self->slots)
    self->slots = Hash_new();
  return Hash_set(self->slots, key, value);
}

Object* Object_getSlot(Object* self, Object* key)
{
  Object* proto = self;

  while (1) {
    if (proto->slots) {
      Object* value = Hash_get(proto->slots, key);
      if (value != Qnil)
        return value;
    }

    if (proto->proto)
      proto = proto->proto;
    else
      break;
  }

  return Qnil;
}

Object* Object_call(Object* self, int argc, Object* argv[])
{
  if (self->proto == CFunction_proto) {
    return CFunction_call(self, 0, argc, argv);
  }
  else if (self->proto == Function_proto) {
    return Function_call(self, 0, argc, argv);
  }
  else {
    Object* excp = Exception_new("called non-function object");
    Exception_raise(excp);
    return Qnil;
  }
}

Object* Object_send(Object* self, Object* key, int argc, Object* argv[])
{
  Object* func = Object_getSlot(self, key);

  if (func->proto == CFunction_proto) {
    return CFunction_call(func, self, argc, argv);
  }
  else if (func->proto == Function_proto) {
    return Function_call(func, self, argc, argv);
  }
  else {
    Object* excp = Exception_new("called non-function object");
    Exception_raise(excp);
    return Qnil;
  }
}

Object* Object_str(Object* self)
{
  return String_new("<Object>");
}

Object* Object_bool(Object* self)
{
  return (self == Qfalse) ? Qfalse : Qtrue;
}

Object* Object_not(Object* self)
{
  Object* bool = Object_send(self, SYM(bool), 0, 0);
  return bool == Qtrue ? Qfalse : Qtrue;
}

void Object_initProto()
{
  Object_setSlot(Object_proto, SYM(new), FUNC(Object_new, 1));
  Object_setSlot(Object_proto, SYM(str), FUNC(Object_str, 1));
  Object_setSlot(Object_proto, SYM(bool), FUNC(Object_bool, 1));
  Object_setSlot(Object_proto, SYM(!), FUNC(Object_not, 1));
}
