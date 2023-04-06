//
// Created by noaho on 11/28/2022.
//

#ifndef FLOOR_NODE_H
#define FLOOR_NODE_H

#include "tree/binary_node.h"

/**
 * @class FloorNode
 * @brief A composite node containing left and right
 *        children. The meaning of this node is left _ right.
 */
class FloorNode : public BinaryNode {
public:
    // Ctor
    FloorNode(ComponentNode* left, ComponentNode* right);

    // Dtor
    ~FloorNode() override = default;

    // Return the printable character stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;
};

#endif // FLOOR_NODE_H
