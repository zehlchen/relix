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

#ifndef RELIX_BLOCK_H
#define RELIX_BLOCK_H

#include "const.h"
#include "opcodes.h"
#include <stdio.h>

typedef struct Block {
  int* data;
  int  size;

  Const** consts;
  int     constc;

  int regc;
} Block;

Block* Block_new();
void   Block_delete(Block* self);

int  Block_append(Block* self, OpCode op, ...);
void Block_replace(Block* self, int pos, int data);
int  Block_position(Block* self);
int  Block_const(Block* self, ConstType type, void* data);

void   Block_write(Block* self, FILE* file);
Block* Block_read(FILE* file);
void   Block_dump(Block* self);

#endif
