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

Object* Integer_new(int value)
{
  Object* new = Object_new(Integer_proto);
  new->data.i = value;
  return new;
}

/*
 * Type conversions
 */

Object* Integer_str(Object* self)
{
  char buffer[20];
  sprintf(buffer, "%d", self->data.i);
  return String_new(buffer);
}

Object* Integer_bool(Object* self)
{
  return self->data.i ? Qtrue : Qfalse;
}

/*
 * Binary operations
 */

Object* Integer_add(Object* self, Object* other)
{
  return Integer_new(self->data.i + other->data.i);
}

Object* Integer_sub(Object* self, Object* other)
{
  return Integer_new(self->data.i - other->data.i);
}

Object* Integer_mul(Object* self, Object* other)
{
  return Integer_new(self->data.i * other->data.i);
}

Object* Integer_div(Object* self, Object* other)
{
  return Integer_new(self->data.i / other->data.i);
}

Object* Integer_eq(Object* self, Object* other)
{
  return self->data.i == other->data.i ? Qtrue : Qfalse;
}

Object* Integer_ne(Object* self, Object* other)
{
  return self->data.i != other->data.i ? Qtrue : Qfalse;
}

Object* Integer_lt(Object* self, Object* other)
{
  return self->data.i < other->data.i ? Qtrue : Qfalse;
}

Object* Integer_gt(Object* self, Object* other)
{
  return self->data.i > other->data.i ? Qtrue : Qfalse;
}

Object* Integer_le(Object* self, Object* other)
{
  return self->data.i <= other->data.i ? Qtrue : Qfalse;
}

Object* Integer_ge(Object* self, Object* other)
{
  return self->data.i >= other->data.i ? Qtrue : Qfalse;
}

Object* Integer_bwand(Object* self, Object* other)
{
  return Integer_new(self->data.i & other->data.i);
}

Object* Integer_bwor(Object* self, Object* other)
{
  return Integer_new(self->data.i | other->data.i);
}

Object* Integer_bwxor(Object* self, Object* other)
{
  return Integer_new(self->data.i ^ other->data.i);
}

Object* Integer_leftshift(Object* self, Object* other)
{
  return Integer_new(self->data.i << other->data.i);
}

Object* Integer_rightshift(Object* self, Object* other)
{
  return Integer_new(self->data.i >> other->data.i);
}

/*
 * Inplace operations
 */

Object* Integer_iadd(Object* self, Object* other)
{
  self->data.i += other->data.i;
  return self;
}

Object* Integer_isub(Object* self, Object* other)
{
  self->data.i -= other->data.i;
  return self;
}

Object* Integer_imul(Object* self, Object* other)
{
  self->data.i *= other->data.i;
  return self;
}

Object* Integer_idiv(Object* self, Object* other)
{
  self->data.i /= other->data.i;
  return self;
}

void Integer_initProto()
{
  Object_setSlot(Integer_proto, SYM(str), FUNC(Integer_str, 1));
  Object_setSlot(Integer_proto, SYM(bool), FUNC(Integer_bool, 1));

  Object_setSlot(Integer_proto, SYM(+), FUNC(Integer_add, 2));
  Object_setSlot(Integer_proto, SYM(-), FUNC(Integer_sub, 2));
  Object_setSlot(Integer_proto, SYM(*), FUNC(Integer_mul, 2));
  Object_setSlot(Integer_proto, SYM(/), FUNC(Integer_div, 2));

  Object_setSlot(Integer_proto, SYM(&), FUNC(Integer_bwand, 2));
  Object_setSlot(Integer_proto, SYM(|), FUNC(Integer_bwor, 2));
  Object_setSlot(Integer_proto, SYM(^), FUNC(Integer_bwxor, 2));

  Object_setSlot(Integer_proto, SYM(<<), FUNC(Integer_leftshift, 2));
  Object_setSlot(Integer_proto, SYM(>>), FUNC(Integer_rightshift, 2));

  Object_setSlot(Integer_proto, SYM(==), FUNC(Integer_eq, 2));
  Object_setSlot(Integer_proto, SYM(!=), FUNC(Integer_ne, 2));
  Object_setSlot(Integer_proto, SYM(<), FUNC(Integer_lt, 2));
  Object_setSlot(Integer_proto, SYM(>), FUNC(Integer_gt, 2));
  Object_setSlot(Integer_proto, SYM(<=), FUNC(Integer_le, 2));
  Object_setSlot(Integer_proto, SYM(>=), FUNC(Integer_ge, 2));

  Object_setSlot(Integer_proto, SYM(+=), FUNC(Integer_iadd, 2));
  Object_setSlot(Integer_proto, SYM(-=), FUNC(Integer_isub, 2));
  Object_setSlot(Integer_proto, SYM(*=), FUNC(Integer_imul, 2));
  Object_setSlot(Integer_proto, SYM(/=), FUNC(Integer_idiv, 2));
}
