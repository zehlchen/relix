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

#include "node.h"
#include <assert.h>

Node* Node_new(enum NodeTag tag, Node* left, Node* right)
{
  Node* node  = malloc(sizeof(Node));
  node->tag   = tag;
  node->left  = left;
  node->right = right;
  return node;
}

void Node_delete(Node* self)
{
  if (self->left)
    Node_delete(self->left);
  if (self->right)
    Node_delete(self->right);

  switch (self->tag) {
    case BinOpNode:
    case GetSlotNode:
    case SetSlotNode:
    case SendNode:
    case SubscriptNode:
      if (self->data.node) {
        Node_delete(self->data.node);
      }
    default:
      break;
  }

  free(self);
}

Node* AssignNode_new(const char* name, Node* value)
{
  Node* node      = Node_new(AssignNode, 0, value);
  node->data.sval = name;
  return node;
}

Node* SubscriptNode_new(Node* obj, Node* subscript, Node* value)
{
  Node* node      = Node_new(SubscriptNode, obj, subscript);
  node->data.node = value;
  return node;
}

Node* BinOpNode_new(Node* lhs, Node* rhs, const char* op)
{
  Node* node                 = Node_new(BinOpNode, lhs, rhs);
  node->data.node            = Node_new(SymbolNode, 0, 0);
  node->data.node->data.sval = op;
  return node;
}

Node* UnOpNode_new(Node* obj, const char* op)
{
  Node* node                 = Node_new(UnOpNode, 0, obj);
  node->data.node            = Node_new(SymbolNode, 0, 0);
  node->data.node->data.sval = op;
  return node;
}

Node* GetSlotNode_new(Node* obj, const char* slot)
{
  Node* node                 = Node_new(GetSlotNode, obj, 0);
  node->data.node            = Node_new(SymbolNode, 0, 0);
  node->data.node->data.sval = slot;
  return node;
}

Node* SetSlotNode_new(Node* obj, Node* val, const char* slot)
{
  Node* node                 = Node_new(SetSlotNode, obj, val);
  node->data.node            = Node_new(SymbolNode, 0, 0);
  node->data.node->data.sval = slot;
  return node;
}

Node* SendNode_new(Node* obj, Node* args, const char* slot)
{
  Node* node                 = Node_new(SendNode, obj, args);
  node->data.node            = Node_new(SymbolNode, 0, 0);
  node->data.node->data.sval = slot;
  return node;
}
