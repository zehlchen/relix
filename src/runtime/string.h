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

#ifndef STRING_H
#define STRING_H

extern Object* String_proto;
void           String_initProto();

Object* String_new(const char*);
Object* String_add(Object* self, Object* other);
Object* String_iadd(Object* self, Object* other);
Object* String_eq(Object* self, Object* other);
Object* String_ne(Object* self, Object* other);
Object* String_bool(Object* self);
Object* String_split(Object* self, Object* delimiter);
Object* String_length(Object* self);

#endif
