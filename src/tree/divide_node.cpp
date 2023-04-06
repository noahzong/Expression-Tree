/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/divide_node.h"
#include "visitors/visitor.h"

// Ctor
DivideNode::DivideNode(ComponentNode* left, ComponentNode* right)
    : BinaryNode(left, right)
{
}

int DivideNode::item() const
{
    return '/';
}

// accept a visitor
void DivideNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}
