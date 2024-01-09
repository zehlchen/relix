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

#include "load.h"
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

#include "memory.h"

Object* load(State* state, const char* name)
{
  char* lib_name = rx_malloc(sizeof(char) * (6 + strlen(name) + strlen(SHARED_LIB_PREFIX) + strlen(SHARED_LIB_SUFFIX)));

  strcpy(lib_name, SHARED_LIB_PREFIX);
  strcat(lib_name, "proty-");
  strcat(lib_name, name);
  strcat(lib_name, SHARED_LIB_SUFFIX);

  void* lib = dlopen(lib_name, RTLD_LAZY);
  if (!lib)
    return Qnil;

  char* init_name = rx_malloc(sizeof(char) * (strlen(name) + 5));
  strcpy(init_name, name);
  strcat(init_name, "_init");

  Object* (*init_func)();
  init_func = dlsym(lib, init_name);

  rx_free(lib_name);
  rx_free(init_name);

  return init_func ? init_func() : Qnil;
}
