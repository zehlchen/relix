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

#ifndef _RELIX_MEMORY_H
#define _RELIX_MEMORY_H

#include "typedef.h"

#define RELIX_ALLOCATOR 1

#ifdef RELIX_ALLOCATOR
void* rx_real_malloc(uint32 size, const char* file, int line);
void* rx_real_calloc(uint32 count, uint32 size, const char* file, int line);
void* rx_real_realloc(void* ptr, uint32 size, const char* file, int line);
void  rx_real_free(void* ptr);

#define rx_malloc(size)        rx_real_malloc(size, __FILE__, __LINE__)
#define rx_calloc(count, size) rx_real_calloc(count, size, __FILE__, __LINE__)
#define rx_realloc(ptr, size)  rx_real_realloc(ptr, size, __FILE__, __LINE__)
#define rx_free(ptr)           rx_real_free(ptr)
#else
#define rx_malloc(size)        malloc(size)
#define rx_calloc(count, size) calloc(count, size)
#define rx_realloc(ptr, size)  realloc(ptr, size)
#define rx_free(ptr)           free(ptr)
#endif /* RELIX_ALLOCATOR */
#endif /* _RELIX_MEMORY_H */