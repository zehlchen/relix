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

#ifndef STATE_H
#define STATE_H

#include <setjmp.h>

typedef int Reg;
struct Object;
struct Module;

typedef struct State {
  int             sp;
  struct Object** stack;
  struct Module*  module;

  jmp_buf        excp_buf;
  struct Object* exception;
} State;

State* State_new(struct Module* module);
void   State_delete(State* self);

void   State_setGlobalState(State* state);
State* State_getGlobalState();

#endif
