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

#include "symtab.h"
#include <stdlib.h>

#define MAX_SCOPE_DEPTH 20

SymTab* SymTab_new()
{
  SymTab* self    = malloc(sizeof(SymTab));
  self->scopes    = malloc(sizeof(Object*) * MAX_SCOPE_DEPTH);
  self->scopes[0] = Hash_new();
  self->scope     = 0;
  return self;
}

void SymTab_delete(SymTab* self)
{
  for (int i = self->scope; i >= 0; i--) {
    Hash_delete(self->scopes[i]);
  }
  free(self->scopes);
  free(self);
}

void SymTab_enterScope(SymTab* self)
{
  self->scope++;
  if (self->scope == MAX_SCOPE_DEPTH)
    abort();
  self->scopes[self->scope] = Hash_new();
}

void SymTab_leaveScope(SymTab* self)
{
  if (self->scope == 0)
    abort();
  Hash_delete(self->scopes[self->scope--]);
}

void SymTab_store(SymTab* self, const char* name, int value)
{
  Object* sym = Symbol_get(name);
  Hash_set(self->scopes[self->scope], sym, Integer_new(value));
}

int SymTab_lookup(SymTab* self, const char* name)
{
  Object* sym = Symbol_get(name);
  for (int i = self->scope; i >= 0; i--) {
    Object* res = Hash_get(self->scopes[i], sym);
    if (res != Qnil)
      return res->data.i;
  }
  return -1;
}
