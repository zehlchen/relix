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

#include "block.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

Block* Block_new()
{
  Block* block = rx_malloc(sizeof(Block));

  block->data = rx_malloc(sizeof(int));
  block->size = 0;

  block->consts = rx_malloc(sizeof(Const));
  block->constc = 0;

  block->regc = 0;

  return block;
}

void Block_delete(Block* self)
{
  for (int i = 0; i < self->constc; i++) {
    Const* c = self->consts[i];
    // rx_free(c->data);
    rx_free(c);
  }

  rx_free(self->data);
  rx_free(self->consts);
  rx_free(self);
}

void Block_replace(Block* self, int pos, int data)
{
  self->data[pos] = data;
}

int Block_append(Block* self, OpCode op, ...)
{
  va_list ap;
  int     start = self->size++;
  int     argc  = OpCode_size(op);

  self->size += argc;
  self->data = rx_realloc(self->data, self->size * sizeof(int));

  self->data[start++] = op;

  va_start(ap, op);
  for (int i = start; i < self->size; i++) {
    self->data[i] = va_arg(ap, int);
  }
  va_end(ap);

  return self->size - argc - 1;
}

int Block_position(Block* self)
{
  return self->size;
}

int Block_const(Block* self, ConstType type, void* data)
{
  Const* constant = rx_malloc(sizeof(Const));
  constant->type  = type;
  constant->data  = data;

  self->consts               = rx_realloc(self->consts, sizeof(Const*) * (self->constc + 1));
  self->consts[self->constc] = constant;
  return self->constc++;
}

void Block_dump(Block* self)
{
  printf("size: %i\n", self->size);
  printf("registers: %i\n", self->regc);
  printf("constants: %i\n", self->constc);

  puts("");

  for (int i = 0; i < self->constc; i++) {
    printf("%02d ", i);
    Const_dump(self->consts[i]);
  }

  puts("");

  for (int i = 0; i < self->size;) {
    OpCode op = self->data[i];
    printf("[%03d] %s\t", i++, OpCode_name(op));
    for (int j = 0; j < OpCode_size(op); j++) {
      printf("%i  ", self->data[i++]);
    }
    puts("");
  }
}

void Block_write(Block* self, FILE* file)
{
  // write data size
  fwrite(&self->size, sizeof(int), 1, file);

  // write data
  fwrite(self->data, sizeof(int), self->size, file);

  // write register count
  fwrite(&self->regc, sizeof(int), 1, file);

  // write constant count
  fwrite(&self->constc, sizeof(int), 1, file);

  // write constants
  for (int i = 0; i < self->constc; i++) {
    Const_write(self->consts[i], file);
  }
}

Block* Block_read(FILE* file)
{
  Block* block = Block_new();

  // read data size
  fread(&block->size, sizeof(int), 1, file);

  // read data
  block->data = rx_malloc(sizeof(int) * block->size);
  fread(block->data, sizeof(int), block->size, file);

  // read register count
  fread(&block->regc, sizeof(int), 1, file);

  // read constant count
  int constc;
  fread(&constc, sizeof(int), 1, file);

  // read constants
  for (int i = 0; i < constc; i++) {
    Const_read(block, file);
  }

  return block;
}
