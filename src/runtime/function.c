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
#include "vm/eval.h"
#include "vm/state.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int id;
  int argc;
} Function;

Object* Function_new(int id, int argc)
{
  Object* new = Object_new(Function_proto);
  Function* f = malloc(sizeof(Function));

  f->id   = id;
  f->argc = argc;

  new->data.ptr = f;
  return new;
}

Object* Function_call(Object* self, Object* fself, int argc, Object* argv[])
{
  Function* function = (Function*) self->data.ptr;

  /// @todo: throw exception
  if (argc != function->argc) {
    printf("proty: call with wrong argument count, expected %i, got %i\n", function->argc, argc);
    abort();
  }

  State* state = State_getGlobalState();

  // push the arguments onto the stack
  for (int i = 0; i < argc; i++) {
    state->stack[state->sp++] = argv[i];
  }

  return eval(state, function->id, argc);
}

int Function_getId(Object* self)
{
  return ((Function*) self->data.ptr)->id;
}

int Function_getArgc(Object* self)
{
  return ((Function*) self->data.ptr)->argc;
}

Object* Function_str(Object* self)
{
  char buffer[15];
  sprintf(buffer, "<Function(%i)>", Function_getArgc(self));
  return String_new(buffer);
}

void Function_initProto()
{
  Object_setSlot(Function_proto, SYM(str), FUNC(Function_str, 1));
}
