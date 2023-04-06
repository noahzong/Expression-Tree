/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/subtract_node.h"
#include "visitors/visitor.h"

// Ctor
SubtractNode::SubtractNode(ComponentNode* left, ComponentNode* right)
    : BinaryNode(left, right)
{
}

int SubtractNode::item() const
{
    return '-';
}

// accept a visitor
void SubtractNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}
