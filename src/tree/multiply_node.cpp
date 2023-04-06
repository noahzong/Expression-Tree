/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/multiply_node.h"
#include "visitors/visitor.h"

// Ctor
MultiplyNode::MultiplyNode(ComponentNode* left, ComponentNode* right)
    : BinaryNode(left, right)
{
}

int MultiplyNode::item() const
{
    return '*';
}

// accept a visitor
void MultiplyNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}
