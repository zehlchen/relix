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

#include "state.h"
#include "module.h"
#include "runtime/runtime.h"
#include <stdlib.h>

#include "memory.h"

static State* global_state = 0;

State* State_new(Module* module)
{
  State* state  = rx_malloc(sizeof(State));
  state->sp     = 0;
  state->stack  = rx_malloc(sizeof(Object*) * 512);
  state->module = module;
  return state;
}

void State_delete(State* self)
{
  rx_free(self->stack);
  rx_free(self);

  if (self == global_state) {
    global_state = 0;
  }
}

void State_setGlobalState(State* state)
{
  global_state = state;
}

State* State_getGlobalState()
{
  return global_state;
}
