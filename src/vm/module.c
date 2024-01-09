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

#include "module.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

#define MAGIC 0x23425250

Module* Module_new()
{
  Module* module = rx_malloc(sizeof(Module));

  module->blocks = rx_malloc(sizeof(Block*));
  module->blockc = 0;

  return module;
}

void Module_delete(Module* self)
{
  for (int i = 0; i < self->blockc; i++) {
    rx_free(self->blocks[i]);
  }
  rx_free(self->blocks);
  rx_free(self);
}

int Module_addBlock(Module* self, Block* block)
{
  self->blocks               = rx_realloc(self->blocks, sizeof(char*) * (self->blockc + 1));
  self->blocks[self->blockc] = block;
  return self->blockc++;
}

void Module_write(Module* self, FILE* file)
{
  // write magic
  int magic = MAGIC;
  fwrite(&magic, sizeof(int), 1, file);

  // write block count
  fwrite(&self->blockc, sizeof(int), 1, file);

  // write blocks
  for (int i = 0; i < self->blockc; i++) {
    Block_write(self->blocks[i], file);
  }
}

Module* Module_read(FILE* file)
{
  Module* module = Module_new();

  // check magic
  int magic;
  fread(&magic, sizeof(int), 1, file);
  assert(magic == MAGIC);

  // read blocks
  int blockc;
  fread(&blockc, sizeof(int), 1, file);

  for (int i = 0; i < blockc; i++) {
    Block* block = Block_read(file);
    Module_addBlock(module, block);
  }

  return module;
}

int Module_probe(FILE* file)
{
  int magic = 0;
  fread(&magic, sizeof(int), 1, file);
  rewind(file);
  return magic == MAGIC;
}

void Module_dump(Module* self)
{
  printf("MODULE DUMP\n");
  for (int i = 0; i < self->blockc; i++) {
    printf("\n#### Block %i\n", i);
    Block_dump(self->blocks[i]);
  }
}
