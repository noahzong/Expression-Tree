/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef TREE_ITERATOR_IMPL_H
#define TREE_ITERATOR_IMPL_H

#include "tree/expression_tree.h"
#include <cstdlib>
#include <queue>
#include <stack>
#include <stdexcept>

// Solve circular include problem
class ComponentNode;
class ExpressionTreeIterator;

/**
 * @class ExpressionTreeIteratorImpl
 * @brief Implementation of the Iterator pattern that is used to define
 *        the various iterations algorithms that can be performed to
 *        traverse the expression tree.
 *
 *        Plays the role of the "implementor" base class in the Bridge
 *        pattern that is used as the basis for the subclasses that
 *        actually define the various iteration algorithms.
 *
 * @see   ExpressionTreeLevelOrderIteratorImpl, ExpressionTreeInOrderIteratorImpl,
 *        ExpressionTreePreOrderIteratorImpl, ExpressionTreePostOrderIteratorImpl,
 */
class ExpressionTreeIteratorImpl {
    friend class ExpressionTreeIterator;

public:
    // Construct an ExpressionTreeIteratorImpl to iterate over a tree.
    explicit ExpressionTreeIteratorImpl(const ExpressionTree& tree);

    // Dtor.
    virtual ~ExpressionTreeIteratorImpl() = default;

    // Dereference operator returns a reference to the item contained
    // at the current position.
    virtual ExpressionTree operator*() = 0;

    // Returns a const reference to the item contained at the current
    // position.
    virtual const ExpressionTree operator*() const = 0;

    // Increment operator (used for both pre- and post-increment).
    virtual void operator++() = 0;

    // Equality operator.
    virtual bool operator==(const ExpressionTreeIteratorImpl& rhs) const = 0;

    // Nonequality operator.
    virtual bool operator!=(const ExpressionTreeIteratorImpl& rhs) const = 0;

    // Method for cloning an impl. Necessary for post increments.
    [[nodiscard]] virtual ExpressionTreeIteratorImpl* clone() const = 0;

    // = Necessary traits
    typedef std::forward_iterator_tag iterator_category;
    typedef int value_type;
    typedef int* pointer;
    typedef int& reference;
    typedef int difference_type;

protected:
    // The tree we are iterating over.
    const ExpressionTree& tree;
};

/**
 * @class InOrderExpressionTreeIteratorImpl
 * @brief Iterates through an ExpressionTree in in-order.
 *
 *        Plays the role of the "implementor" class in the Bridge
 *        pattern that defines the in-order iteration algorithm.
 */
class InOrderExpressionTreeIteratorImpl : public ExpressionTreeIteratorImpl {
    friend class ExpressionTreeIterator;

public:
    // Construct an InOrderExpressionTreeIteratorImpl. If end_iter
    // is set to true, the iterator points to the end of the
    // tree. Otherwise, the iterator starts with a free tree.
    explicit InOrderExpressionTreeIteratorImpl(const ExpressionTree& tree, bool endIter = false);

    // Dtor.
    ~InOrderExpressionTreeIteratorImpl() override = default;

    // Dereference operator returns a reference to the item contained
    // at the current position.
    ExpressionTree operator*() override;

    // Returns a const reference to the item contained at the current
    // position.
    const ExpressionTree operator*() const override;

    // Increment operator (used for both pre- and post-increment).
    void operator++() override;

    // Equality operator.
    bool operator==(const ExpressionTreeIteratorImpl& rhs) const override;

    // Nonequality operator.
    bool operator!=(const ExpressionTreeIteratorImpl& lhs) const override;

    // Method for cloning an impl. Necessary for post increments.
    ExpressionTreeIteratorImpl* clone() const override;

    // = Necessary traits
    typedef std::forward_iterator_tag iterator_category;
    typedef int value_type;
    typedef int* pointer;
    typedef int& reference;
    typedef int difference_type;

private:
    // Our current position in the iteration.
    std::stack<ExpressionTree> stack;
};

/**
 * @class PreOrderExpressionTreeIteratorImpl
 * @brief Iterates through an ExpressionTree in level-order.
 *
 *        Plays the role of the "implementor" class in the Bridge
 *        pattern that defines the level-order iteration algorithm.
 */
class PreOrderExpressionTreeIteratorImpl : public ExpressionTreeIteratorImpl {
    friend class ExpressionTreeIterator;

public:
    // Construct an PreOrderExpressionTreeIteratorImpl. If end_iter
    // is set to true, the iterator points to the end of the
    // tree. Otherwise, the iterator starts with a free tree.
    explicit PreOrderExpressionTreeIteratorImpl(const ExpressionTree& tree, bool endIter = false);

    // Dtor.
    ~PreOrderExpressionTreeIteratorImpl() override = default;

    // Dereference operator returns a reference to the item contained
    // at the current position.
    ExpressionTree operator*() override;

    // Returns a const reference to the item contained at the current
    // position.
    const ExpressionTree operator*() const override;

    // Increment operator (used for both pre- and post-increment).
    void operator++() override;

    // Equality operator.
    bool operator==(const ExpressionTreeIteratorImpl& rhs) const override;

    // Nonequality operator.
    bool operator!=(const ExpressionTreeIteratorImpl& lhs) const override;

    // Method for cloning an impl. Necessary for post increments.
    ExpressionTreeIteratorImpl* clone() const override;

    // = Necessary traits
    typedef std::forward_iterator_tag iterator_category;
    typedef int value_type;
    typedef int* pointer;
    typedef int& reference;
    typedef int difference_type;

private:
    // Our current position in the iteration.
    std::stack<ExpressionTree> stack;
};

/**
 * @class PostOrderExpressionTreeIteratorImpl
 * @brief Iterates through an ExpressionTree in post-order.
 *
 *        Plays the role of the "implementor" class in the Bridge
 *        pattern that defines the post-order iteration algorithm.
 */
class PostOrderExpressionTreeIteratorImpl : public ExpressionTreeIteratorImpl {
    friend class ExpressionTreeIterator;

public:
    // Construct an PostOrderExpressionTreeIteratorImpl. If end_iter is set
    // to true, the iterator points to the end of the tree. Otherwise,
    // the iterator starts with a free tree.
    explicit PostOrderExpressionTreeIteratorImpl(const ExpressionTree& tree, bool end_iter = false);

    // Dtor.
    ~PostOrderExpressionTreeIteratorImpl() override = default;

    // Dereference operator returns a reference to the item contained
    // at the current position.
    ExpressionTree operator*() override;

    // Returns a const reference to the item contained at the current
    // position.
    const ExpressionTree operator*() const override;

    // Increment operator (used for both pre- and post-increment).
    void operator++() override;

    // Equality operator.
    bool operator==(const ExpressionTreeIteratorImpl& rhs) const override;

    // Nonequality operator.
    bool operator!=(const ExpressionTreeIteratorImpl& lhs) const override;

    // Method for cloning an impl. Necessary for post increments.
    ExpressionTreeIteratorImpl* clone() const override;

    // = Necessary traits
    typedef std::forward_iterator_tag iterator_category;
    typedef int value_type;
    typedef int* pointer;
    typedef int& reference;
    typedef int difference_type;

private:
    // Our current position in the iteration.
    std::stack<ExpressionTree> stack;
};

/**
 * @class LevelOrderExpressionTreeIteratorImpl
 * @brief Iterates through an ExpressionTree in level-order.
 *
 *        Plays the role of the "implementor" class in the Bridge
 *        pattern that defines the post-order iteration algorithm.
 */
class LevelOrderExpressionTreeIteratorImpl : public ExpressionTreeIteratorImpl {
    friend class ExpressionTreeIterator;

public:
    // Construct an LevelOrderExpressionTreeIteratorImpl. If end_iter is set to
    // true, the iterator points to the end of the tree. Otherwise, the
    // iterator starts with a free tree.
    explicit LevelOrderExpressionTreeIteratorImpl(
        const ExpressionTree& tree, bool end_iter = false);

    // Dtor.
    ~LevelOrderExpressionTreeIteratorImpl() override = default;

    // Dereference operator returns a reference to the item contained
    // at the current position.
    ExpressionTree operator*() override;

    // Returns a const reference to the item contained at the current
    // position.
    const ExpressionTree operator*() const override;

    // Increment operator (used for both pre- and post-increment).
    void operator++() override;

    // Equality operator.
    bool operator==(const ExpressionTreeIteratorImpl& rhs) const override;

    // Nonequality operator.
    bool operator!=(const ExpressionTreeIteratorImpl& lhs) const override;

    // Method for cloning an impl. Necessary for post increments.
    ExpressionTreeIteratorImpl* clone() const override;

    // = Necessary traits
    typedef std::forward_iterator_tag iterator_category;
    typedef int value_type;
    typedef int* pointer;
    typedef int& reference;
    typedef int difference_type;

private:
    // Our current position in the iteration.
    // @@ Consider zapping this.
    std::queue<ExpressionTree> queue;
};

#endif // TREE_ITERATOR_IMPL_H
