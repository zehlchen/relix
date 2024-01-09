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

#include "runtime.h"
#include <stdio.h>

Object* Object_proto    = 0;
Object* CFunction_proto = 0;
Object* Function_proto  = 0;
Object* Hash_proto      = 0;
Object* List_proto      = 0;
Object* Symbol_proto    = 0;
Object* Bool_proto      = 0;
Object* Integer_proto   = 0;
Object* Float_proto     = 0;
Object* String_proto    = 0;
Object* Exception_proto = 0;

Object* Qnil   = 0;
Object* Qtrue  = 0;
Object* Qfalse = 0;

void runtime_init()
{
  Object_proto    = Object_new(0);
  CFunction_proto = Object_new(Object_proto);
  Function_proto  = Object_new(Object_proto);
  Hash_proto      = Object_new(Object_proto);
  List_proto      = Object_new(Object_proto);
  Symbol_proto    = Object_new(Object_proto);
  Bool_proto      = Object_new(Object_proto);
  Integer_proto   = Object_new(Object_proto);
  Float_proto     = Object_new(Object_proto);
  String_proto    = Object_new(Object_proto);
  Exception_proto = Object_new(Object_proto);

  SymbolTable_init();
  Object_initProto();
  CFunction_initProto();
  Function_initProto();
  Hash_initProto();
  List_initProto();
  Symbol_initProto();
  Bool_initProto();
  Integer_initProto();
  Float_initProto();
  String_initProto();
  Exception_initProto();

  Qnil   = Nil_new();
  Qtrue  = Bool_new();
  Qfalse = Bool_new();
}
