/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/binary_node.h"

// Ctor
BinaryNode::BinaryNode(ComponentNode* left, ComponentNode* right)
    : UnaryNode(right)
    , leftChild(left)
{
}

// Return the left child pointer
ComponentNode* BinaryNode::left() const
{
    return leftChild.get();
}
