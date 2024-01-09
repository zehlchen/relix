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

typedef struct {
  int          size;
  int          bounds;
  const char** keys;
  Object**     values;
} Symtab;

Symtab* symtab;

void SymbolTable_init()
{
  symtab         = malloc(sizeof(Symtab));
  symtab->keys   = calloc(sizeof(char*), 64);
  symtab->values = malloc(sizeof(Object*) * 64);

  symtab->bounds = 64;
  symtab->size   = 0;
}

/*
 * Generates an integer hash of a string value. This function should
 * generate hashes fast and with a low collision rate.
 */

static unsigned int hash_string(const char* str)
{
  unsigned int hash = 5381;
  int          c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

/*
 * Returns a symbol for the given string. If this symbol is not
 * already in the symbol table, a new symbol will be created.
 */

Object* Symbol_get(const char* id)
{
  unsigned int hash = hash_string(id);
  unsigned int pos  = hash % symtab->bounds;

  // search for the key
  while (symtab->keys[pos]) {
    if (strcmp(symtab->keys[pos], id)) {
      pos = (pos + 1) % symtab->bounds;
    }
    else
      return symtab->values[pos];
  }

  // key not found, create a new symbol
  pos = hash % symtab->bounds;

  while (symtab->keys[pos] && strcmp(symtab->keys[pos], id)) {
    pos = (pos + 1) % symtab->bounds;
  }

  Object* symbol = Object_new(Symbol_proto);

  symtab->keys[pos]   = id;
  symtab->values[pos] = symbol;
  symtab->size++;

  return symbol;
}

void Symbol_initProto()
{
  Symbol_proto->data.ptr = symtab;
}
