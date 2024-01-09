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

#ifndef RELIX_COMPILER_H
#define RELIX_COMPILER_H

#include "node.h"
#include "symtab.h"
#include <setjmp.h>
#include <vm/block.h>
#include <vm/module.h>

/**
 * Holds the compilation context.
 */
typedef struct Context {
  /// the module
  Module* module;

  /// the current block
  Block* block;

  /// the symbol table
  SymTab* symtab;

  /// the register count
  int reg;

  /// error handling
  jmp_buf error_buf;
} Context;

/**
 * Creates a new compilation Context.
 * @param module The module.
 * @returns The new context;
 */
Context* Compiler_newContext(Module* module);

/**
 * Deletes a Context.
 * @param context The context to delete.
 */
void Compiler_deleteContext(Context* context);

/**
 * Compiles a file to a Block.
 * @param context The compilation context.
 * @param file The file descriptor.
 * @returns The index of the compiled Block.
 */
int Compiler_compileFile(Context* context, FILE* file);

/**
 * Compiles a string to a Block.
 * @param context The compilation context.
 * @param string The string.
 * @returns The index of the compiled Block.
 */
int Compiler_compileString(Context* context, const char* string);

/**
 * Compiles a root node a Block.
 * @param context The compilation context.
 * @param root The root node.
 * @returns The index of the compiled Block.
 */
int Compiler_compileRootNode(Context* context, Node* root);

/**
 * Compiles a node in the current context.
 * @param context The compilation context.
 * @param node The node.
 * @returns The register of the result.
 */
int Compiler_compile(Context* context, Node* node);

#endif
