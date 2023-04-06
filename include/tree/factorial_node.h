//
// Created by noaho on 11/28/2022.
//

#ifndef FACTORIAL_NODE_H
#define FACTORIAL_NODE_H

#include "tree/unary_node.h"

/**
 * @class FactorialNode
 * @brief A composite node containing only a left child.
 *        The meaning of this node is left!, eg 5!, 7!, etc.
 */
class FactorialNode : public UnaryNode {
public:
    // Ctor
    explicit FactorialNode(ComponentNode* left);

    // Dtor
    ~FactorialNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // FACTORIAL_NODE_H
