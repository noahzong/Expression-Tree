//
// Created by noaho on 11/27/2022.
//
#include "tree/factorial_node.h"
#include "visitors/visitor.h"

// Ctor
FactorialNode::FactorialNode(ComponentNode* left)
    : UnaryNode(left)
{
}

int FactorialNode::item() const
{
    return '!';
}

// accept a visitor
void FactorialNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}
