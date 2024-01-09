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

typedef struct {
  FuncPtr func;
  int     argc;
} CFunction;

Object* CFunction_new(FuncPtr func, int argc)
{
  Object* new  = Object_new(CFunction_proto);
  CFunction* f = rx_malloc(sizeof(CFunction));

  f->func = func;
  f->argc = argc;

  new->data.ptr = f;
  return new;
}

Object* CFunction_call(Object* self, Object* fself, int argc, Object* argv[])
{
  CFunction* function = (CFunction*) self->data.ptr;

  if (argc != function->argc) {
    Object* excp = Exception_new("wrong argument count");
    Exception_raise(excp);
  }

  if (!fself)
    fself = Qnil;

  FuncPtr func = function->func;
  Object* ret;
  switch (argc) {
    case 0:
      ret = func(fself);
      break;
    case 1:
      ret = func(fself, argv[0]);
      break;
    case 2:
      ret = func(fself, argv[0], argv[1]);
      break;
    case 3:
      ret = func(fself, argv[0], argv[1], argv[2]);
      break;
    case 4:
      ret = func(fself, argv[0], argv[1], argv[2], argv[3]);
      break;
    case 5:
      ret = func(fself, argv[0], argv[1], argv[2], argv[3], argv[4]);
      break;
    case 6:
      ret = func(fself, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]);
      break;
    case 7:
      ret = func(fself, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
      break;
    default:
      ret = Qnil;
  }

  return ret;
}

Object* CFunction_str(Object* self)
{
  char buffer[16];
  sprintf(buffer, "<CFunction(%i)>", ((CFunction*) self->data.ptr)->argc);
  return String_new(buffer);
}

void CFunction_initProto()
{
  Object_setSlot(CFunction_proto, SYM(str), FUNC(CFunction_str, 1));
}
