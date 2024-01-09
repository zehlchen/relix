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

#ifndef RELIX_OPCODE_H
#define RELIX_OPCODE_H

typedef enum OpCode {
  // general instructions
  OP_HLT,
  OP_NOP,
  OP_MOV,
  OP_RET,
  OP_JMP,
  OP_JNS,
  OP_FUN,
  OP_LOAD,

  // primitives
  OP_SYM,
  OP_INT,
  OP_FLOAT,
  OP_STR,
  OP_BOOL,
  OP_NIL,
  OP_LIST,
  OP_HASH,

  // object methods
  OP_SET,
  OP_GET,
  OP_CALL,
  OP_SEND,

  // exception handling
  OP_TRY,
  OP_ENDTRY,

  // stack operations
  OP_PUSH,
  OP_POP,
} OpCode;

const char* OpCode_name(OpCode op);
int         OpCode_size(OpCode op);

#endif
