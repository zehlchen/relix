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

Object* Float_new(double value)
{
  Object* new = Object_new(Float_proto);
  new->data.d = value;
  return new;
}

/*
 * Type conversions
 */

Object* Float_str(Object* self)
{
  char buffer[20];
  sprintf(buffer, "%f", self->data.d);
  return String_new(buffer);
}

Object* Float_bool(Object* self)
{
  return self->data.d ? Qtrue : Qfalse;
}

/*
 * Binary operations
 */

Object* Float_add(Object* self, Object* other)
{
  return Float_new(self->data.d + other->data.d);
}

Object* Float_sub(Object* self, Object* other)
{
  return Float_new(self->data.d - other->data.d);
}

Object* Float_mul(Object* self, Object* other)
{
  return Float_new(self->data.d * other->data.d);
}

Object* Float_div(Object* self, Object* other)
{
  return Float_new(self->data.d / other->data.d);
}

Object* Float_eq(Object* self, Object* other)
{
  return self->data.d == other->data.d ? Qtrue : Qfalse;
}

Object* Float_ne(Object* self, Object* other)
{
  return self->data.d != other->data.d ? Qtrue : Qfalse;
}

Object* Float_lt(Object* self, Object* other)
{
  return self->data.d < other->data.d ? Qtrue : Qfalse;
}

Object* Float_gt(Object* self, Object* other)
{
  return self->data.d > other->data.d ? Qtrue : Qfalse;
}

Object* Float_le(Object* self, Object* other)
{
  return self->data.d <= other->data.d ? Qtrue : Qfalse;
}

Object* Float_ge(Object* self, Object* other)
{
  return self->data.d >= other->data.d ? Qtrue : Qfalse;
}

/*
 * Inplace operations
 */

Object* Float_iadd(Object* self, Object* other)
{
  self->data.d += other->data.d;
  return self;
}

Object* Float_isub(Object* self, Object* other)
{
  self->data.d -= other->data.d;
  return self;
}

Object* Float_imul(Object* self, Object* other)
{
  self->data.d *= other->data.d;
  return self;
}

Object* Float_idiv(Object* self, Object* other)
{
  self->data.d /= other->data.d;
  return self;
}

void Float_initProto()
{
  Object_setSlot(Float_proto, SYM(str), FUNC(Float_str, 1));
  Object_setSlot(Float_proto, SYM(bool), FUNC(Float_bool, 1));

  Object_setSlot(Float_proto, SYM(+), FUNC(Float_add, 2));
  Object_setSlot(Float_proto, SYM(-), FUNC(Float_sub, 2));
  Object_setSlot(Float_proto, SYM(*), FUNC(Float_mul, 2));
  Object_setSlot(Float_proto, SYM(/), FUNC(Float_div, 2));

  Object_setSlot(Float_proto, SYM(==), FUNC(Float_eq, 2));
  Object_setSlot(Float_proto, SYM(!=), FUNC(Float_ne, 2));
  Object_setSlot(Float_proto, SYM(<), FUNC(Float_lt, 2));
  Object_setSlot(Float_proto, SYM(>), FUNC(Float_gt, 2));
  Object_setSlot(Float_proto, SYM(<=), FUNC(Float_le, 2));
  Object_setSlot(Float_proto, SYM(>=), FUNC(Float_ge, 2));

  Object_setSlot(Float_proto, SYM(+=), FUNC(Float_iadd, 2));
  Object_setSlot(Float_proto, SYM(-=), FUNC(Float_isub, 2));
  Object_setSlot(Float_proto, SYM(*=), FUNC(Float_imul, 2));
  Object_setSlot(Float_proto, SYM(/=), FUNC(Float_idiv, 2));
}
