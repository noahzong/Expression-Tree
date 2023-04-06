//
// Created by noaho on 11/27/2022.
//

#ifndef MODULUS_NODE_H
#define MODULUS_NODE_H

#include "tree/binary_node.h"

/**
 * @class DivideNode
 * @brief A composite node containing left and right
 *        children. The meaning of this node is left / right.
 */
class ModulusNode : public BinaryNode {
public:
    // Ctor
    ModulusNode(ComponentNode* left, ComponentNode* right);

    // Dtor
    ~ModulusNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // MODULUS_NODE_H
