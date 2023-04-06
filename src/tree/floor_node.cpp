//
// Created by noaho on 11/28/2022.
//

#include "tree/floor_node.h"
#include "visitors/visitor.h"

// Ctor
FloorNode::FloorNode(ComponentNode* left, ComponentNode* right)
    : BinaryNode(left, right)
{
}

int FloorNode::item() const
{
    return '_';
}

// accept a visitor
void FloorNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}