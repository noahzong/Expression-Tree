/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef SUBTRACT_NODE_H
#define SUBTRACT_NODE_H

#include "tree/binary_node.h"

/**
 * @class SubtractNode
 * @brief A composite node containing left and right
 *        children. The meaning of this node is left - right
 */
class SubtractNode : public BinaryNode {
public:
    // Ctor
    SubtractNode(ComponentNode* left, ComponentNode* right);

    // Dtor
    ~SubtractNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // SUBTRACT_NODE_H
