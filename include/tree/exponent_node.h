//
// Created by noaho on 11/27/2022.
//

#ifndef EXPONENT_NODE_H
#define EXPONENT_NODE_H

#include "tree/binary_node.h"

/**
 * @class ExponentNode
 * @brief A composite node containing left and right
 *        children. The meaning of this node is left ^ right.
 */
class ExponentNode : public BinaryNode {
public:
    // Ctor
    ExponentNode(ComponentNode* left, ComponentNode* right);

    // Dtor
    ~ExponentNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // EXPONENT_NODE_H
