/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/unary_node.h"

// Ctor
UnaryNode::UnaryNode(ComponentNode* right)
    : ComponentNode()
    , rightChild(right)
{
}

// Return the right child pointer
ComponentNode* UnaryNode::right() const
{
    return rightChild.get();
}
