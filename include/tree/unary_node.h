/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef UNARY_NODE_H
#define UNARY_NODE_H

#include "tree/component_node.h"
#include <memory>

/**
 * @class UnaryNode
 * @brief Defines a right child (but not a left one) and thus is useful for
 * unary operations.
 * @see BinaryNode
 */
class UnaryNode : public ComponentNode {
public:
    // Ctor
    explicit UnaryNode(ComponentNode* right);

    // Dtor
    ~UnaryNode() override = default;

    // Return the right child.
    [[nodiscard]] ComponentNode* right() const override;

private:
    // Right child
    std::unique_ptr<ComponentNode> rightChild;
};

#endif // UNARY_NODE_H
