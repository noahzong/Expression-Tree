/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/leaf_node.h"
#include "visitors/visitor.h"

// Ctor
LeafNode::LeafNode(int item)
    : ComponentNode()
    , value(item)
{
}

// Ctor
LeafNode::LeafNode(const std::string& item)
    : ComponentNode()
{
    value = atoi(item.c_str());
}

// Ctor
LeafNode::LeafNode(const char* item)
    : ComponentNode()
{
    value = atoi(item);
}

// return the item
int LeafNode::item() const
{
    return value;
}

void LeafNode::accept(Visitor& visitor) const
{
    visitor.visit(*this);
}
