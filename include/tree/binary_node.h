/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "tree/unary_node.h"

/**
 * @class Composite_Binary_Node
 * @brief Defines a left and right node (via inheritance).
 */
class BinaryNode : public UnaryNode {
public:
    // Ctor
    BinaryNode(ComponentNode* left, ComponentNode* right);

    // Dtor
    ~BinaryNode() override = default;

    // Return the left child.
    [[nodiscard]] ComponentNode* left() const override;

private:
    // left child
    std::unique_ptr<ComponentNode> leftChild;
};

#endif // BINARY_NODE_H
