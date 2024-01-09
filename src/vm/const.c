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

#include "const.h"
#include "block.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

void Const_write(Const* self, FILE* file)
{
  // write type
  fwrite(&self->type, sizeof(ConstType), 1, file);

  // write constant data
  switch (self->type) {
    case CONST_SYM:
    case CONST_STR: {
      size_t length = strlen(self->data);
      fwrite(&length, sizeof(size_t), 1, file);
      fwrite(self->data, sizeof(char), length, file);
      break;
    }

    case CONST_FLOAT:
      fwrite(self->data, sizeof(double), 1, file);
      break;
  }
}

void Const_read(Block* block, FILE* file)
{
  // read type
  ConstType type;
  fread(&type, sizeof(ConstType), 1, file);

  // read data
  switch (type) {
    case CONST_SYM:
    case CONST_STR: {
      size_t length;
      fread(&length, sizeof(size_t), 1, file);

      char* data = rx_malloc(sizeof(char) * length);
      fread(data, sizeof(char), length, file);

      Block_const(block, type, data);
      break;
    }

    case CONST_FLOAT: {
      double* data = rx_malloc(sizeof(double));
      fread(data, sizeof(double), 1, file);
      Block_const(block, CONST_FLOAT, data);
      break;
    }
  }
}

void Const_dump(Const* self)
{
  switch (self->type) {
    case CONST_SYM:
      printf("SYMBOL %s\n", (char*) self->data);
      break;

    case CONST_STR:
      printf("STRING %s\n", (char*) self->data);
      break;

    case CONST_FLOAT:
      printf("FLOAT  %f\n", *((double*) self->data));
      break;
  }
}
