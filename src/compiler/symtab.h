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

#ifndef RELIX_SYMTAB_H
#define RELIX_SYMTAB_H

#include <runtime/runtime.h>

typedef struct SymTab {
  Object** scopes;
  int      scope;
} SymTab;

SymTab* SymTab_new();
void    SymTab_delete(SymTab* self);

void SymTab_enterScope(SymTab* self);
void SymTab_leaveScope(SymTab* self);
void SymTab_store(SymTab* self, const char* name, int value);
int  SymTab_lookup(SymTab* self, const char* name);

#endif
