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
#ifndef RELIX_AST_H
#define RELIX_AST_H

#include <stdlib.h>

typedef struct Node {
  enum NodeTag {
    BranchNode,
    BinOpNode,
    UnOpNode,
    CallNode,
    SendNode,

    ArgsNode,
    DoArgsNode,
    HashArgsNode,

    SetSlotNode,
    GetSlotNode,
    AssignNode,
    SubscriptNode,

    IfNode,
    ElseNode,
    WhileNode,
    DoNode,
    TryNode,

    HashNode,
    HashElementNode,
    ListNode,
    IntegerNode,
    FloatNode,
    StringNode,
    NameNode,
    SymbolNode,
  } tag;

  union {
    int          ival;
    double       dval;
    const char*  sval;
    struct Node* node;
  } data;

  struct Node* left;
  struct Node* right;
} Node;

Node* Node_new(enum NodeTag tag, Node* left, Node* right);
void  Node_delete(Node* self);

Node* AssignNode_new(const char* name, Node* value);
Node* SubscriptNode_new(Node* obj, Node* subscript, Node* value);
Node* BinOpNode_new(Node* lhs, Node* rhs, const char* op);
Node* UnOpNode_new(Node* obj, const char* op);
Node* GetSlotNode_new(Node* obj, const char* slot);
Node* SetSlotNode_new(Node* obj, Node* val, const char* slot);
Node* SendNode_new(Node* obj, Node* args, const char* slot);

#endif
