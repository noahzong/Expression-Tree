/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/negate_node.h"
#include "visitors/visitor.h"

// Ctor
NegateNode::NegateNode(ComponentNode* right)
    : UnaryNode(right)
{
}

int NegateNode::item() const
{
    return '-';
}

// accept a visitor
void NegateNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}
