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
#include <stdlib.h>
#include <string.h>

#include "memory.h"

typedef struct {
  int      size;
  int      bounds;
  Object** keys;
  Object** values;
} Hash;

/*
 * Generates an integer hash of a string value. This function should
 * generate hashes fast and with a low collision rate.
 */

static unsigned hash_str(const char* str)
{
  unsigned hash = 5381;
  int      c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

/*
 * Generates a hash of a memory address.
 * http://www.concentric.net/~ttwang/tech/addrhash.htm
 */

static unsigned hash_addr(void* addr)
{
  unsigned long key = (unsigned long) addr;
  return (unsigned) (((key >> 3) * 2654435761) % 0x80000000);
}

/*
 * Invokes the matching hash function.
 */

static unsigned hash_obj(Object* obj)
{
  if (obj->proto == String_proto) {
    return hash_str(obj->data.ptr);
  }
  else if (obj->proto == Symbol_proto) {
    return hash_addr(obj);
  }
  else {
    return Object_send(obj, SYM(hash), 0, 0)->data.i;
  }
}

/*
 * Tests objects for equality.
 */

static int cmp_obj(Object* a, Object* b)
{
  if (a->proto == Symbol_proto) {
    return a == b;
  }
  else if (a->proto == String_proto) {
    if (b->proto == String_proto) {
      return strcmp(a->data.ptr, b->data.ptr) ? 0 : 1;
    }
    else {
      return 0;
    }
  }
  else {
    return Object_send(a, SYM(==), 1, &b) == Qtrue;
  }
}

Object* Hash_init(Object* self)
{
  Hash* hash = rx_malloc(sizeof(Hash));

  hash->size   = 0;
  hash->bounds = 8;

  hash->keys   = rx_calloc(sizeof(Object*), hash->bounds);
  hash->values = rx_malloc(sizeof(Object*) * hash->bounds);

  self->data.ptr = hash;
  return self;
}

Object* Hash_new()
{
  Object* new = Object_new(Hash_proto);
  Hash_init(new);
  return new;
}

Object* Hash_delete(Object* self)
{
  Hash* hash = self->data.ptr;

  rx_free(hash->keys);
  rx_free(hash->values);
  rx_free(hash);

  return Object_delete(self);
}

Object* Hash_set(Object* self, Object* key, Object* value)
{
  Hash* hash = self->data.ptr;

  // double the hash bounds if the hash is more than 75% full
  if ((hash->size * 100) / hash->bounds > 75) {
    int newBounds = hash->bounds * 2;

    Object** tmpKeys   = rx_calloc(sizeof(Object*), newBounds);
    Object** tmpValues = rx_malloc(sizeof(Object*) * newBounds);

    // rehash each key
    for (int i = 0; i < hash->bounds; i++) {
      if (hash->keys[i]) {
        unsigned int pos = hash_obj(hash->keys[i]) % newBounds;
        while (tmpKeys[pos] && !cmp_obj(hash->keys[i], tmpKeys[pos])) {
          pos = (pos + 1) % newBounds;
        }
        tmpKeys[pos]   = hash->keys[i];
        tmpValues[pos] = hash->values[i];
      }
    }

    rx_free(hash->keys);
    rx_free(hash->values);

    hash->keys   = tmpKeys;
    hash->values = tmpValues;

    hash->bounds = newBounds;
  }

  unsigned int pos = hash_obj(key) % hash->bounds;

  while (hash->keys[pos] && !cmp_obj(hash->keys[pos], key)) {
    pos = (pos + 1) % hash->bounds;
  }

  hash->keys[pos]   = key;
  hash->values[pos] = value;
  hash->size++;

  return value;
}

Object* Hash_get(Object* self, Object* key)
{
  Hash*        hash = (Hash*) self->data.ptr;
  unsigned int pos  = hash_obj(key) % hash->bounds;
  while (hash->keys[pos]) {
    if (!cmp_obj(hash->keys[pos], key)) {
      pos = (pos + 1) % hash->bounds;
    }
    else {
      return hash->values[pos];
    }
  }
  return Qnil;
}

Object* Hash_size(Object* self)
{
  Hash* hash = self->data.ptr;
  return Integer_new(hash->size);
}

void Hash_initProto()
{
  // bootstrap hash prototype
  Hash_proto->slots = Object_new(Hash_proto);
  Hash_init(Hash_proto->slots);

  Object_setSlot(Hash_proto, SYM(init), FUNC(Hash_init, 1));
  Object_setSlot(Hash_proto, SYM([]), FUNC(Hash_get, 2));
  Object_setSlot(Hash_proto, SYM([] =), FUNC(Hash_set, 3));
  Object_setSlot(Hash_proto, SYM(size), FUNC(Hash_size, 1));
}
