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

Object* Bool_str(Object* self)
{
  if (self == Qtrue)
    return String_new("<true>");
  else
    return String_new("<false>");
}

Object* Bool_eq(Object* self, Object* other)
{
  if (other == self)
    return Qtrue;
  Object* otherBool = Object_send(other, SYM(bool), 0, 0);
  return self == otherBool ? Qtrue : Qfalse;
}

Object* Bool_and(Object* self, Object* other)
{
  return (self == Qtrue && other == Qtrue) ? Qtrue : Qfalse;
}

Object* Bool_or(Object* self, Object* other)
{
  return (self == Qtrue || other == Qtrue) ? Qtrue : Qfalse;
}

Object* Bool_not(Object* self)
{
  return self == Qtrue ? Qfalse : Qtrue;
}

Object* Bool_new()
{
  return Object_new(Bool_proto);
}

void Bool_initProto()
{
  Object_setSlot(Bool_proto, SYM(==), FUNC(Bool_eq, 2));
  Object_setSlot(Bool_proto, SYM(and), FUNC(Bool_and, 2));
  Object_setSlot(Bool_proto, SYM(or), FUNC(Bool_or, 2));
  Object_setSlot(Bool_proto, SYM(not ), FUNC(Bool_not, 1));
  Object_setSlot(Bool_proto, SYM(str), FUNC(Bool_str, 1));
}
