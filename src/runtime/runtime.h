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

#ifndef RUNTIME_H
#define RUNTIME_H

typedef struct Object Object;
typedef Object* (*FuncPtr)(Object*, ...);

#include "bool.h"
#include "cfunction.h"
#include "exception.h"
#include "float.h"
#include "function.h"
#include "hash.h"
#include "integer.h"
#include "list.h"
#include "nil.h"
#include "object.h"
#include "string.h"
#include "symbol.h"
#include "typedef.h"
#include "vm/state.h"

#define FUNC(name, argc) CFunction_new((FuncPtr) name, argc - 1)
#define SYM(name)        Symbol_get(#name)

void runtime_init();

#endif
