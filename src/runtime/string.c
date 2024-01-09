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
#include <stdlib.h>
#include <string.h>

#include "memory.h"

Object* String_new(const char* value)
{
  Object* new   = Object_new(String_proto);
  new->data.ptr = rx_malloc(strlen(value) + 1);
  strcpy(new->data.ptr, value);
  return new;
}

Object* String_add(Object* self, Object* other)
{
  int   size   = strlen(self->data.ptr) + strlen(other->data.ptr) + 1;
  char* buffer = rx_malloc(size);
  strcpy(buffer, self->data.ptr);
  strcat(buffer, other->data.ptr);
  Object* str = String_new(buffer);
  rx_free(buffer);
  return str;
}

Object* String_iadd(Object* self, Object* other)
{
  int size       = strlen(self->data.ptr) + strlen(other->data.ptr) + 1;
  self->data.ptr = rx_realloc(self->data.ptr, size);
  strcat(self->data.ptr, other->data.ptr);
  return self;
}

Object* String_eq(Object* self, Object* other)
{
  return strcmp(self->data.ptr, other->data.ptr) ? Qfalse : Qtrue;
}

Object* String_ne(Object* self, Object* other)
{
  return strcmp(self->data.ptr, other->data.ptr) ? Qtrue : Qfalse;
}

Object* String_bool(Object* self)
{
  return strlen(self->data.ptr) ? Qtrue : Qfalse;
}

Object* String_split(Object* self, Object* delimiter)
{
  const char* str = self->data.ptr;
  const char* del = delimiter->data.ptr;

  const char* str_end  = str + strlen(str);
  size_t      del_size = strlen(del);

  Object* list = List_new();

  char* pch;
  pch = strstr(str, del);

  while (str < str_end) {
    size_t size = pch - str;

    if (size != 0) {
      char* tmp = rx_calloc(sizeof(char), size + 1);
      strncpy(tmp, str, size);

      List_append(list, String_new(tmp));

      rx_free(tmp);
    }

    str += size + del_size;
    pch = strstr(str, del);
    if (pch == 0)
      pch = (char*) str_end;
  }

  return list;
}

Object* String_length(Object* self)
{
  return Integer_new(strlen(self->data.ptr));
}

void String_initProto()
{
  Object_setSlot(String_proto, SYM(+), FUNC(String_add, 2));
  Object_setSlot(String_proto, SYM(+=), FUNC(String_iadd, 2));

  Object_setSlot(String_proto, SYM(==), FUNC(String_eq, 2));
  Object_setSlot(String_proto, SYM(!=), FUNC(String_ne, 2));

  Object_setSlot(String_proto, SYM(bool), FUNC(String_bool, 1));
  Object_setSlot(String_proto, SYM(length), FUNC(String_length, 1));
  Object_setSlot(String_proto, SYM(split), FUNC(String_split, 2));
}
