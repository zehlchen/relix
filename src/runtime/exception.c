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
#include "vm/state.h"
#include <stdio.h>
#include <stdlib.h>

Object* Exception_new(const char* str)
{
  Object* excp   = Object_new(Exception_proto);
  excp->data.ptr = (void*) str;
  return excp;
}

Object* Exception_raise(Object* self)
{
  State* state     = State_getGlobalState();
  state->exception = self;

  longjmp(state->excp_buf, 1);

  // never reached
  return Qnil;
}

void Exception_initProto()
{
  Object_setSlot(Exception_proto, SYM(raise), FUNC(Exception_raise, 1));
}
