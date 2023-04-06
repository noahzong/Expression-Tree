/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef DIVIDE_NODE_H
#define DIVIDE_NODE_H

#include "tree/binary_node.h"

/**
 * @class DivideNode
 * @brief A composite node containing left and right
 *        children. The meaning of this node is left / right.
 */
class DivideNode : public BinaryNode {
public:
    // Ctor
    DivideNode(ComponentNode* left, ComponentNode* right);

    // Dtor
    ~DivideNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // DIVIDE_NODE_H
