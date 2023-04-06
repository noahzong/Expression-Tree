/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef LEAF_NODE_H
#define LEAF_NODE_H

#include "tree/component_node.h"
#include <string>

/**
 * @class LeafNode
 * @brief Defines a terminal node of type integer. This node inherits
 *        from Node and so has no children.
 */

class LeafNode : public ComponentNode {
public:
    // Ctor.
    explicit LeafNode(int item);

    // Ctor.
    explicit LeafNode(const std::string& item);

    // Ctor.
    explicit LeafNode(const char* item);

    // Dtor.
    ~LeafNode() override = default;

    // Return the item stored in the node.
    [[nodiscard]] int item() const override;

    // Define the accept() operation used for the Visitor pattern.
    void accept(Visitor& visitor) const override;

private:
    // Integer value associated with the operand.
    int value;
};

#endif // LEAF_NODE_H
