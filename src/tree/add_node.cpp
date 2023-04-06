/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/add_node.h"
#include "visitors/visitor.h"

// Ctor
AddNode::AddNode(ComponentNode* left, ComponentNode* right)
    : BinaryNode(left, right)
{
}

int AddNode::item() const
{
    return '+';
}

// accept a visitor
void AddNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}
