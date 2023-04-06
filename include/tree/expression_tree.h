/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef EXPRESSION_TREE_H
#define EXPRESSION_TREE_H

#include "refcounter.h"
#include "tree/component_node.h"
#include <stdexcept>
#include <string>

// Forward declarations.
class ExpressionTreeIterator;
class ExpressionTreeConstIterator;

/**
 * @class ExpressionTree
 * @brief Interface for the Composite pattern that is used to contain
 *        all the operator and operand nodes in the expression tree.
 *
 *        Plays the role of the "abstraction" class in the Bridge
 *        pattern and delegates to the appropriate "implementor"
 *        that performs the expression tree operations.  Also
 *        defines the STL factory methods that create the desired
 *        begin and end iterators.
 */
class ExpressionTree {
public:
    // Exception class for Invalid States exceptions
    class InvalidIterator : public std::domain_error {
    public:
        explicit InvalidIterator(const std::string& message)
            : std::domain_error(message)
        {
        }
    };

    // Define a "trait"
    using value_type = int;
    using iterator = ExpressionTreeIterator;
    using const_iterator = ExpressionTreeConstIterator;

    // Default ctor
    ExpressionTree();

    // Ctor that takes a Node * that contains all the nodes in the expression tree.
    explicit ExpressionTree(ComponentNode* root, bool increment = false);

    // Copy ctor
    ExpressionTree(const ExpressionTree& rhs);

    // Gain access to the underlying root pointer functions are useful
    // to the iterators.
    ComponentNode* getRoot();

    // Assignment operator.
    ExpressionTree& operator=(const ExpressionTree& t);

    bool operator==(const ExpressionTree& rhs) const;

    // Dtor
    ~ExpressionTree() = default;

    // Check if tree is null tree.
    [[nodiscard]] bool isNull() const;

    // Return the item in the tree.
    [[nodiscard]] int item() const;

    // Return the left child.
    ExpressionTree left();

    // Return the right child.
    ExpressionTree right();

    // Get an iterator pointing to the "beginning" of the expression
    // tree relative to the requested traversalOrder.
    iterator begin(const std::string& traversalOrder);

    // Get an iterator pointing to the "end" of the expression tree
    // relative to the requested traversalOrder.
    iterator end(const std::string& traversalOrder);

    // Get a const iterator pointing to the "beginning" of the
    // expression tree relative to the requested traversalOrder.
    [[nodiscard]] const_iterator begin(const std::string& traversalOrder) const;

    // Get a const iterator pointing to the "end" of the expression
    // tree relative to the requested traversalOrder.
    [[nodiscard]] const_iterator end(const std::string& traversalOrder) const;

    // Accept a visitor to perform some action on the Expression_Tree.
    void accept(Visitor& visitor) const;

private:
    // Pointer to actual implementation, i.e., the "bridge", which is
    // reference counted to automate memory management.
    Refcounter<ComponentNode> root;
    //    std::shared_ptr<ComponentNode> root;
};

#endif // EXPRESSION_TREE_H
