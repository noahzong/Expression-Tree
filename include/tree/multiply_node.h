/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef MULTIPLY_NODE_H
#define MULTIPLY_NODE_H

#include "tree/binary_node.h"

/**
 * @class MultiplyNode
 * @brief A composite node containing left and right
 *        children. The meaning of this node is left * right
 */
class MultiplyNode : public BinaryNode {
public:
    // Ctor
    MultiplyNode(ComponentNode* left, ComponentNode* right);

    // Dtor
    ~MultiplyNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // MULTIPLY_NODE_H
