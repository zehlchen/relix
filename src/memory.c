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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "typedef.h"

static uint32 _rx_mem_allocs    = 0;
static uint32 _rx_mem_reallocs  = 0;
static uint32 _rx_mem_deallocs  = 0;
static uint32 _rx_mem_bytes     = 0;
static uint32 _rx_mem_max_bytes = 0;

typedef struct AllocRecord {
  uint32 size;
  uint32 alloc_id;
  uint8* file;
  uint32 line;

  struct AllocRecord* next;
  struct AllocRecord* prev;

  uint8 pad[40 - (sizeof(uint32) + sizeof(uint32) + sizeof(uint8*) + sizeof(uint32) + sizeof(void*) + sizeof(void*))];
} AllocRecord;

static AllocRecord* _rx_mem_block = NULL;

static AllocRecord* pointer_to_record(void* ptr)
{
  return (AllocRecord*) (((uint8*) ptr) - sizeof(AllocRecord));
}

static void* record_to_pointer(AllocRecord* block)
{
  return (void*) (((uint8*) block) + sizeof(AllocRecord));
}

static AllocRecord* rx_base_block()
{
  if (!_rx_mem_block)
    _rx_mem_block = calloc(1, sizeof(AllocRecord));

  return _rx_mem_block;
}

static void AllocRecord_remove(AllocRecord* self)
{
  if (self->next)
    self->next->prev = self->prev;

  if (self->prev)
    self->prev->next = self->next;
}

static void AllocRecord_insert(AllocRecord* self, AllocRecord* other)
{
  self->next  = other->next;
  self->prev  = other;
  other->next = self;

  if (self->next)
    self->next->prev = self;
}

static AllocRecord* AllocRecord_new(uint32 size, uint8* file, uint32 line)
{
  AllocRecord* self = (AllocRecord*) calloc(1, sizeof(AllocRecord) + size);

  self->size     = size;
  self->alloc_id = _rx_mem_allocs;
  self->file     = file;
  self->line     = line;

  AllocRecord_insert(self, rx_base_block());

  _rx_mem_allocs++;
  _rx_mem_bytes += size;

  if (_rx_mem_bytes > _rx_mem_max_bytes)
    _rx_mem_max_bytes = _rx_mem_bytes;

  return self;
}

static AllocRecord* AllocRecord_realloc(AllocRecord* self, uint32 size, uint8* file, uint32 line)
{
  AllocRecord* prev = self->prev;

  AllocRecord_remove(self);

  _rx_mem_bytes -= self->size;
  _rx_mem_bytes += size;
  _rx_mem_reallocs++;

  self       = (AllocRecord*) realloc(self, sizeof(AllocRecord) + size);
  self->size = size;
  self->file = file;
  self->line = line;

  AllocRecord_insert(self, prev);

  return self;
}

static void AllocRecord_free(AllocRecord* self)
{
  AllocRecord_remove(self);

  _rx_mem_bytes -= self->size;
  _rx_mem_deallocs++;

  free(self);
}

static uint32 AllocRecord_size(AllocRecord* self)
{
  return self->size;
}

static void AllocRecord_print(AllocRecord* self)
{
  uint8* file = strrchr(self->file, '/');
  file        = file ? file + 1 : self->file;

  fprintf(stderr, "#\t%i %p %s:%i\t%i\n", self->alloc_id, record_to_pointer(self), file, self->line, self->size);
}

void* rx_real_malloc(uint32 size, const char* file, int line)
{
  AllocRecord* self = AllocRecord_new(size, (uint8*) file, line);

  return record_to_pointer(self);
}

void* rx_real_calloc(uint32 count, uint32 size, const char* file, int line)
{
  return rx_real_malloc(count * size, file, line);
}

void* rx_real_realloc(void* ptr, uint32 size, const char* file, int line)
{
  if (ptr) {
    AllocRecord* self = AllocRecord_realloc(pointer_to_record(ptr), size, (uint8*) file, line);

    return record_to_pointer(self);
  }

  return rx_real_malloc(size, file, line);
}

void rx_real_free(void* ptr)
{
  AllocRecord_free(pointer_to_record(ptr));
}

void rx_mem_print()
{
  AllocRecord* block = rx_base_block();

  fprintf(stderr, "### Memory Usage\n");
  fprintf(stderr, "#   Allocations: %i\n", _rx_mem_allocs);
  fprintf(stderr, "# Reallocations: %i\n", _rx_mem_reallocs);
  fprintf(stderr, "# Deallocations: %i\n", _rx_mem_deallocs);
  fprintf(stderr, "#         Bytes: %i\n", _rx_mem_bytes);
  fprintf(stderr, "#     Max Bytes: %i\n", _rx_mem_max_bytes);

  fprintf(stderr, "\n");

  fprintf(stderr, "Allocations:\n");

  while (block->next) {
    block = block->next;

    AllocRecord_print(block);
  }
}