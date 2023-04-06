//
// Created by noaho on 11/28/2022.
//

#ifndef CEILING_NODE_H
#define CEILING_NODE_H

#include "tree/binary_node.h"

/**
 * @class CeilingNode
 * @brief A composite node containing left and right
 *        children. The meaning of this node is left | right.
 */
class CeilingNode : public BinaryNode {
public:
    // Ctor
    CeilingNode(ComponentNode* left, ComponentNode* right);

    // Dtor
    ~CeilingNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // CEILING_NODE_H
