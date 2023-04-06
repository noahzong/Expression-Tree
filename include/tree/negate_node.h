/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef NEGATE_NODE_H
#define NEGATE_NODE_H

#include "tree/unary_node.h"

/**
 * @class NegateNode
 * @brief A composite node containing only a right child.
 *        The meaning of this node is -right, eg -5, -7, etc.
 */
class NegateNode : public UnaryNode {
public:
    // Ctor
    explicit NegateNode(ComponentNode* right);

    // Dtor
    ~NegateNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // NEGATE_NODE_H
