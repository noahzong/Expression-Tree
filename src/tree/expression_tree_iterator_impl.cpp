/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/expression_tree_iterator_impl.h"
#include "tree/component_node.h"
#include "tree/expression_tree.h"

// Constructor for ExpressionTreeIteratorImpl that takes a tree
// to iterate over
ExpressionTreeIteratorImpl::ExpressionTreeIteratorImpl(const ExpressionTree& tree)
    : tree(tree)
{
}

// Construct an InOrderExpressionTreeIteratorImpl. If end_iter is set to true,
// the iterator points to the end of the tree
InOrderExpressionTreeIteratorImpl::InOrderExpressionTreeIteratorImpl(
    const ExpressionTree& tree, bool end_iter)
    : ExpressionTreeIteratorImpl(tree)
    , stack()
{
    // if the caller doesn't want an end iterator, insert the root tree
    // into the queue.
    if (!end_iter && !tree.isNull()) {
        stack.push(const_cast<ExpressionTree&>(tree));

        // start at the smallest element (left-most)
        while (!stack.top().left().isNull())
            stack.push(stack.top().left());
    }
}

// Returns the Node that the iterator is pointing to (non-const version)
ExpressionTree InOrderExpressionTreeIteratorImpl::operator*()
{
    return stack.top();
}

// Returns the Node that the iterator is pointing to (const version)

const ExpressionTree InOrderExpressionTreeIteratorImpl::operator*() const
{
    return stack.top();
}

// moves the iterator to the next node (pre-increment)

void InOrderExpressionTreeIteratorImpl::operator++()
{
    // we know that at this point there is no left () of top ()
    // because we would have already visited it.

    if (!stack.empty()) {
        // if we have nodes greater than ourselves
        if (!stack.top().right().isNull()) {
            // push the right child node onto the stack
            // and pop the old parent (it's been visited now)
            auto val = stack.top();
            stack.pop();
            stack.push(val.right());

            // keep pushing until we get to the left most child
            while (!stack.top().left().isNull())
                stack.push(stack.top().left());
        } else
            stack.pop();
    }
}

// checks two iterators for equality

bool InOrderExpressionTreeIteratorImpl::operator==(const ExpressionTreeIteratorImpl& rhs) const
{
    auto inOrderRhs = dynamic_cast<const InOrderExpressionTreeIteratorImpl*>(&rhs);

    // if the rhs was not a levelOrder iterator then we've already
    // discovered the relation is false.

    if (inOrderRhs) {
        // Check if the container we are iterating over has the same
        // root node and that the size of the queues are equal. The
        // latter doesn't truly determine equality. However, this is an
        // easy check for determining most inequalities and it allows us
        // to assume the queue at least has a front node (coupled with
        // the is_empty () function later).

        auto t1 = const_cast<ExpressionTree&>(tree);
        auto t2 = const_cast<ExpressionTree&>(inOrderRhs->tree);

        if (t1.getRoot() == t2.getRoot() && stack.size() == inOrderRhs->stack.size()) {
            // Check for both being empty (special condition).
            if (stack.empty() && inOrderRhs->stack.empty())
                return true;

            // check the front's node pointer. If the node pointers are
            // equal, then both iterators are pointing to the same
            // position in the tree.
            if (stack.top() == inOrderRhs->stack.top())
                return true;
        }
    }

    // either we were trying to compare a non-level order iterator or we
    // were comparing two level order iterators that were obviously at
    // different points in the tree (their queue sizes were different)
    return false;
}

// checks two iterators for inequality
bool InOrderExpressionTreeIteratorImpl::operator!=(const ExpressionTreeIteratorImpl& rhs) const
{
    return !(*this == rhs);
}

// Method for cloning an impl. Necessary for post increments (bridge)
// @see Expression_Tree_Iterator
ExpressionTreeIteratorImpl* InOrderExpressionTreeIteratorImpl::clone() const
{
    return new InOrderExpressionTreeIteratorImpl(*this);
}

// Construct an PreOrderExpressionTreeIteratorImpl. If end_iter is set to true,
// the iterator points to the end of the tree
PreOrderExpressionTreeIteratorImpl::PreOrderExpressionTreeIteratorImpl(
    const ExpressionTree& tree, bool end_iter)
    : ExpressionTreeIteratorImpl(tree)
    , stack()
{
    // if the caller doesn't want an end iterator, insert the root tree
    // into the queue.
    if (!end_iter && !tree.isNull())
        stack.push(const_cast<ExpressionTree&>(tree));
}

// Returns the Node that the iterator is pointing to (non-const version)
ExpressionTree PreOrderExpressionTreeIteratorImpl::operator*()
{
    return stack.top();
}

// Returns the Node that the iterator is pointing to (const version)
const ExpressionTree PreOrderExpressionTreeIteratorImpl::operator*() const
{
    return stack.top();
}

// moves the iterator to the next node (pre-increment)
void PreOrderExpressionTreeIteratorImpl::operator++()
{
    // we know that at this point there is no left () of top ()
    // because we would have already visited it.

    if (!stack.empty()) {
        // we need to pop the node off the stack before pushing the
        // children, or else we'll revisit this node later

        ExpressionTree current = stack.top();
        stack.pop();

        // note the order here: right first, then left. Since this is
        // LIFO, this results in the left child being the first
        // evaluated, which fits into the Pre-order traversal strategy

        if (!current.right().isNull())
            stack.push(current.right());
        if (!current.left().isNull())
            stack.push(current.left());
    }
}

// checks two iterators for equality
bool PreOrderExpressionTreeIteratorImpl::operator==(const ExpressionTreeIteratorImpl& rhs) const
{
    auto pre_order_rhs = dynamic_cast<const PreOrderExpressionTreeIteratorImpl*>(&rhs);

    // if the rhs was not a level_order iterator
    // then we've already discovered the relation is false

    if (pre_order_rhs) {
        // check if the container we are iterating over has the same
        // root node and that the size of the queues are equal. The
        // latter doesn't truly determine equality. However, this is an
        // easy check for determining most inequalities and it allows us
        // to assume the queue at least has a front node (coupled with
        // the is_empty () function later).

        auto t1 = const_cast<ExpressionTree&>(tree);
        auto t2 = const_cast<ExpressionTree&>(pre_order_rhs->tree);

        if (t1.getRoot() == t2.getRoot() && stack.size() == pre_order_rhs->stack.size()) {
            // check for both being is_empty (special condition)
            if (stack.empty() && pre_order_rhs->stack.empty())
                return true;

            // check the front's node pointer. If the node pointers
            // are equal, then both iterators are pointing to the same
            // position in the tree.

            if (stack.top() == pre_order_rhs->stack.top())
                return true;
        }
    }

    // either we were trying to compare a non-level order iterator or
    // we were comparing two level order iterators that were obviously
    // at different points in the tree (their queue sizes were different)

    return false;
}

// checks two iterators for inequality
bool PreOrderExpressionTreeIteratorImpl::operator!=(const ExpressionTreeIteratorImpl& rhs) const
{
    return !(*this == rhs);
}

// Method for cloning an impl. Necessary for post increments (bridge)
// @see Expression_Tree_Iterator
ExpressionTreeIteratorImpl* PreOrderExpressionTreeIteratorImpl::clone() const
{
    return new PreOrderExpressionTreeIteratorImpl(*this);
}

// Construct an PostOrderExpressionTreeIteratorImpl. If end_iter is set to
// true,
// the iterator points to the end of the tree
PostOrderExpressionTreeIteratorImpl::PostOrderExpressionTreeIteratorImpl(
    const ExpressionTree& tree, bool end_iter)
    : ExpressionTreeIteratorImpl(tree)
    , stack()
{
    // if the caller doesn't want an end iterator, insert the root tree
    // into the queue.
    if (!end_iter && !tree.isNull()) {
        ExpressionTree current = const_cast<ExpressionTree&>(tree);
        stack.push(current);

        // the commented code does not work on unary operator nodes with no left
        // child, but
        // a right child - or at least, there is a certain depth that this will not
        // go down

        while (!current.isNull()) {
            if (!current.right().isNull())
                stack.push(current.right());
            if (!current.left().isNull()) {
                // if there was a left, then update current
                // this is the case for all non-negations
                stack.push(current.left());
                current = current.left();
            } else
                // if there was not a left, then current = current->right_
                // this handles cases of unary nodes, like negations
                current = current.right();
        }
    }
}

// Returns the Node that the iterator is pointing to (non-const version)
ExpressionTree PostOrderExpressionTreeIteratorImpl::operator*()
{
    return stack.top();
}

// Returns the Node that the iterator is pointing to (const version)
const ExpressionTree PostOrderExpressionTreeIteratorImpl::operator*() const
{
    return stack.top();
}

// moves the iterator to the next node (pre-increment)
void PostOrderExpressionTreeIteratorImpl::operator++()
{
    // we know that at this point there is no left () of top ()
    // because we would have already visited it.

    if (!stack.empty()) {
        // we need to pop the node off the stack before pushing the
        // children, or else we'll revisit this node later

        ExpressionTree current = stack.top();
        stack.pop();

        // This is where stuff gets a little confusing.

        if (!stack.empty() && stack.top().left().getRoot() != current.getRoot()
            && stack.top().right().getRoot() != current.getRoot()) {
            current = stack.top();

            while (!current.isNull()) {
                if (!current.right().isNull())
                    stack.push(current.right());
                if (!current.left().isNull()) {
                    // if there was a left, then update current
                    // this is the case for all non-negations
                    stack.push(current.left());
                    current = current.left();
                } else {
                    // if there was not a left, then current = current->right_
                    // this handles cases of unary nodes, like negations
                    current = current.right();
                }
            }
        }
    }
}

// checks two iterators for equality

bool PostOrderExpressionTreeIteratorImpl::operator==(const ExpressionTreeIteratorImpl& rhs) const
{
    auto postOrderRhs = dynamic_cast<const PostOrderExpressionTreeIteratorImpl*>(&rhs);

    // if the rhs was not a level_order iterator
    // then we've already discovered the relation is false

    if (postOrderRhs) {
        // check if the container we are iterating over has the same
        // root node and that the size of the queues are equal. The
        // latter doesn't truly determine equality. However, this is an
        // easy check for determining most inequalities and it allows us
        // to assume the queue at least has a front node (coupled with
        // the is_empty () function later).

        auto t1 = const_cast<ExpressionTree&>(tree);
        auto t2 = const_cast<ExpressionTree&>(postOrderRhs->tree);

        if (t1.getRoot() == t2.getRoot() && stack.size() == postOrderRhs->stack.size()) {
            // check for both being is_empty (special condition)
            if (stack.empty() && postOrderRhs->stack.empty())
                return true;

            // check the front's node pointer. If the node pointers are
            // equal, then both iterators are pointing to the same
            // position in the tree.

            if (stack.top() == postOrderRhs->stack.top())
                return true;
        }
    }

    // either we were trying to compare a non-level order iterator or
    // we were comparing two level order iterators that were obviously
    // at different points in the tree (their queue sizes were different)

    return false;
}

// checks two iterators for inequality
bool PostOrderExpressionTreeIteratorImpl::operator!=(const ExpressionTreeIteratorImpl& rhs) const
{
    return !(*this == rhs);
}

// Method for cloning an impl. Necessary for post increments (bridge)
// @see Expression_Tree_Iterator
ExpressionTreeIteratorImpl* PostOrderExpressionTreeIteratorImpl::clone() const
{
    return new PostOrderExpressionTreeIteratorImpl(*this);
}

// Construct an LevelOrderExpressionTreeIteratorImpl. If end_iter is set to
// true, the iterator points to the end of the tree

LevelOrderExpressionTreeIteratorImpl::LevelOrderExpressionTreeIteratorImpl(
    const ExpressionTree& tree, bool end_iter)
    : ExpressionTreeIteratorImpl(tree)
    , queue()
{
    // if the caller doesn't want an end iterator, insert the root tree
    // into the queue.
    if (!end_iter && !tree.isNull())
        queue.push(const_cast<ExpressionTree&>(tree));
}

// Returns the Node that the iterator is pointing to (non-const version)
ExpressionTree LevelOrderExpressionTreeIteratorImpl::operator*()
{
    return queue.front();
}

// Returns the Node that the iterator is pointing to (const version)
const ExpressionTree LevelOrderExpressionTreeIteratorImpl::operator*() const
{
    return queue.front();
}

// moves the iterator to the next node (pre-increment)
void LevelOrderExpressionTreeIteratorImpl::operator++()
{
    if (!queue.empty()) {
        // If the queue is not empty, dequeue an element
        ExpressionTree root = queue.front();
        queue.pop();

        if (!root.isNull()) {
            // If the element wasn't null, enqueue its children
            if (!root.left().isNull())
                queue.push(root.left());
            if (!root.right().isNull())
                queue.push(root.right());
        }
    }
}

// checks two iterators for equality
bool LevelOrderExpressionTreeIteratorImpl::operator==(const ExpressionTreeIteratorImpl& rhs) const
{
    auto level_order_rhs = dynamic_cast<const LevelOrderExpressionTreeIteratorImpl*>(&rhs);

    // if the rhs was not a level_order iterator then we've already
    // discovered the relation is false.

    if (level_order_rhs) {
        // check if the container we are iterating over has the same
        // root node and that the size of the queues are equal. The
        // latter doesn't truly determine equality. However, this is an
        // easy check for determining most inequalities and it allows us
        // to assume the queue at least has a front node (coupled with
        // the is_empty () function later).

        auto t1 = const_cast<ExpressionTree&>(tree);
        auto t2 = const_cast<ExpressionTree&>(level_order_rhs->tree);

        if (t1.getRoot() == t2.getRoot() && queue.size() == level_order_rhs->queue.size()) {
            // check for both being is_empty (special condition)
            if (queue.empty() && level_order_rhs->queue.empty())
                return true;

            // check the front's node pointer. If the node pointers
            // are equal, then both iterators are pointing to the same
            // position in the tree.

            if (queue.front() == level_order_rhs->queue.front())
                return true;
        }
    }

    // either we were trying to compare a non-level order iterator or we
    // were comparing two level order iterators that were obviously at
    // different points in the tree (their queue sizes were different)

    return false;
}

// checks two iterators for inequality
bool LevelOrderExpressionTreeIteratorImpl::operator!=(const ExpressionTreeIteratorImpl& rhs) const
{
    return !(*this == rhs);
}

// Method for cloning an impl. Necessary for post increments (bridge)
// @see Expression_Tree_Iterator
ExpressionTreeIteratorImpl* LevelOrderExpressionTreeIteratorImpl::clone() const
{
    return new LevelOrderExpressionTreeIteratorImpl(*this);
}
