/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef TREE_ITERATOR_H
#define TREE_ITERATOR_H

#include <memory>
#include <string>

// Forward declarations.
class ExpressionTree;
class ExpressionTreeIteratorImpl;

/**
 * @class ExpressionTreeIterator
 * @brief Interface for the Iterator pattern that is used traverse
 *        through all the nodes in the expression tree in a non-const
 *        manner.
 *
 *        Plays the role of the "abstraction" class in the Bridge
 *        pattern and delegates to the appropriate "implementor"
 *        that performs the appropriate expression tree iterator
 *        operations.
 *
 * @see   LevelOrderIteratorImpl, InOrderIteratorImpl,
 *         PreOrderIteratorImpl, and Post_Order_Iterator_Impl.
 */
class ExpressionTreeIterator {
public:
    // = Necessary traits
    using iterator_category = std::forward_iterator_tag;
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using difference_type = int;

    // Copy ctor - needed for reference counting.
    ExpressionTreeIterator(const ExpressionTreeIterator& ts) = default;

    // Copy ctor for impl *.
    explicit ExpressionTreeIterator(ExpressionTreeIteratorImpl* impl);

    // Dereference operator returns a reference to the item contained at the current position
    ExpressionTree operator*();

    // Returns a const reference to the item contained at the current position
    const ExpressionTree operator*() const;

    // Pre-increment operator
    ExpressionTreeIterator& operator++();

    // Post-increment operator.
    const ExpressionTreeIterator operator++(int);

    // Equality operator
    bool operator==(const ExpressionTreeIterator& rhs);

    // In-equality operator
    bool operator!=(const ExpressionTreeIterator& rhs);

private:
    // Pointer to actual implementation, i.e., the "bridge"
    std::shared_ptr<ExpressionTreeIteratorImpl> impl;
};

/**
 * @class ExpressionTreeConstIterator
 * @brief Interface for the Iterator pattern that is used traverse
 *        through all the nodes in the expression tree in a const
 *        manner.
 *
 *        Plays the role of the "abstraction" class in the Bridge
 *        pattern and delegates to the appropriate "implementation"
 *        that performs the appropriate expression tree iterator
 *        operations.
 *
 * @see   ExpressionTreeLevelOrderIteratorImpl, ExpressionTreeInOrderIteratorImpl,
 *        ExpressionTreePreOrderIteratorImpl, and ExpressionTreePostOrderIteratorImpl.
 */
class ExpressionTreeConstIterator {
public:
    // Copy ctor - needed for reference counting.
    ExpressionTreeConstIterator(const ExpressionTreeConstIterator& ts) = default;

    // Copy ctor for impl *.
    explicit ExpressionTreeConstIterator(ExpressionTreeIteratorImpl* impl);

    // Returns a const reference to the item contained at the current position
    const ExpressionTree operator*() const;

    // Pre-increment operator
    ExpressionTreeConstIterator& operator++();

    // Post-increment operator.
    const ExpressionTreeConstIterator operator++(int);

    // Equality operator
    bool operator==(const ExpressionTreeConstIterator& rhs);

    // Nonequality operator
    bool operator!=(const ExpressionTreeConstIterator& rhs);

    // = Necessary traits
    typedef std::forward_iterator_tag iterator_category;
    typedef int value_type;
    typedef int* pointer;
    typedef int& reference;
    typedef int difference_type;

private:
    // Pointer to actual implementation, i.e., the "bridge"
    std::shared_ptr<ExpressionTreeIteratorImpl> impl;
};

#endif // TREE_ITERATOR_H
