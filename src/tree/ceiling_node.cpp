//
// Created by noaho on 11/28/2022.
//

#include "tree/ceiling_node.h"
#include "visitors/visitor.h"

// Ctor
CeilingNode::CeilingNode(ComponentNode* left, ComponentNode* right)
    : BinaryNode(left, right)
{
}

int CeilingNode::item() const
{
    return '|';
}

// accept a visitor
void CeilingNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}