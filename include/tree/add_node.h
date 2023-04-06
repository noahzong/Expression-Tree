/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef ADD_NODE_H
#define ADD_NODE_H

#include "tree/binary_node.h"

/**
 * @class AddNode
 * @brief A composite node containing left and right
 *        children. The meaning of this node is left + right
 */
class AddNode : public BinaryNode {
public:
    // Ctor
    AddNode(ComponentNode* left, ComponentNode* right);

    // Dtor
    ~AddNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // ADD_NODE_H
