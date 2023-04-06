/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef COMPONENT_NODE_H
#define COMPONENT_NODE_H

#include <stdexcept>

// Forward declaration.
class Visitor;

/**
 * @class ComponentNode
 * @brief An abstract base class defines a simple abstract
 *        implementation of an expression tree node.
 *
 *        This class plays the role of the "Component" in the
 *        Composite pattern.  The methods in this class are not
 *        defined as pure virtual so that subclasses in the Composite
 *        pattern don't have to implement methods they don't care
 *        about.
 *
 * @see   See CompositeUnaryNode and CompositeBinaryNode for nodes
 *        with right only and left and right children, respectively.
 */
class ComponentNode {
public:
    // Dtor
    virtual ~ComponentNode() = default;

    // Return the item stored in the node
    [[nodiscard]] virtual int item() const = 0;

    // Return the left child (returns nullptr if called directly).
    [[nodiscard]] virtual ComponentNode* left() const;

    // Return the right child (returns nullptr if called directly).
    [[nodiscard]] virtual ComponentNode* right() const;

    // Accept a visitor to perform some action on the node's item
    // completely arbitrary visitor template
    virtual void accept(Visitor& visitor) const = 0;
};

#endif // COMPONENT_NODE_H
