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

#ifndef RELIX_TOKEN_H
#define RELIX_TOKEN_H

typedef enum TokenType {
  // operators
  Token_binaryop,
  Token_unaryop,
  Token_assign,

  // primitive data types
  Token_integer,
  Token_decimal,
  Token_string,
  Token_name,

  // keywords
  Token_doKw,
  Token_ifKw,
  Token_elseKw,
  Token_whileKw,
  Token_endKw,
  Token_tryKw,
  Token_catchKw,

  // braces
  Token_lpar,
  Token_rpar,
  Token_lsqb,
  Token_rsqb,
  Token_lbrace,
  Token_rbrace,

  // other symbols
  Token_comma,
  Token_dot,
  Token_colon,
  Token_semicolon,
  Token_hash,
  Token_excl,
  Token_arrow,

  Token_newline,
  Token_eof,
  Token_unknown,
} TokenType;

typedef struct Token {
  TokenType   type;
  const char* value;
  int         lineno;
  int         precedence;
} Token;

#endif
