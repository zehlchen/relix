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

#include <assert.h>
#include <stdio.h>

#include "node.h"

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

void Node_print(Node* node, int indent)
{
  assert(node);

  if (indent == 0) {
    fprintf(stderr, "Begin AST dump:\n");
  }

  for (int i = 0; i < indent; i++)
    fprintf(stderr, "--");

  fprintf(stderr, "> ");

  switch (node->tag) {
    case BranchNode:
      fprintf(stderr, "BranchNode");
      break;
    case BinOpNode:
      fprintf(stderr, "BinOpNode");
      break;
    case UnOpNode:
      fprintf(stderr, "UnOpNode");
      break;
    case CallNode:
      fprintf(stderr, "CallNode");
      break;
    case SendNode:
      fprintf(stderr, "SendNode");
      break;

    case ArgsNode:
      fprintf(stderr, "ArgsNode");
      break;
    case DoArgsNode:
      fprintf(stderr, "DoArgsNode");
      break;
    case HashArgsNode:
      fprintf(stderr, "HashArgsNode");
      break;
    case SetSlotNode:
      fprintf(stderr, "SetSlotNode");
      break;
    case GetSlotNode:
      fprintf(stderr, "GetSlotNode");
      break;
    case AssignNode:
      fprintf(stderr, "AssignNode");
      break;
    case SubscriptNode:
      fprintf(stderr, "SubscriptNode");
      break;

    case IfNode:
      fprintf(stderr, "IfNode");
      break;
    case ElseNode:
      fprintf(stderr, "ElseNode");
      break;
    case WhileNode:
      fprintf(stderr, "WhileNode");
      break;
    case DoNode:
      fprintf(stderr, "DoNode");
      break;
    case TryNode:
      fprintf(stderr, "TryNode");
      break;

    case HashNode:
      fprintf(stderr, "HashNode");
      break;
    case HashElementNode:
      fprintf(stderr, "HashElementNode");
      break;
    case ListNode:
      fprintf(stderr, "ListNode");
      break;
    case IntegerNode:
      fprintf(stderr, "IntegerNode");
      break;
    case FloatNode:
      fprintf(stderr, "FloatNode");
      break;
    case StringNode:
      fprintf(stderr, "StringNode");
      break;
    case NameNode:
      fprintf(stderr, "NameNode");
      break;
    case SymbolNode:
      fprintf(stderr, "SymbolNode");
      break;
    default:
      fprintf(stderr, "UnknownNode");
      break;
  }
  fprintf(stderr, "\n");

  fflush(stderr);

  if (node->left)
    Node_print(node->left, indent + 1);
  if (node->right)
    Node_print(node->right, indent + 1);

  if (indent == 0)
    fprintf(stderr, "End AST dump.\n");
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
