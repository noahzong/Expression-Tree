/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/expression_tree.h"
#include "tree/component_node.h"
#include "tree/expression_tree_iterator.h"
#include "tree/expression_tree_iterator_impl.h"
#include <algorithm>
#include <map>
#include <sstream>
#include <stdexcept>

/**
 * @class ExpressionTreeIteratorFactory
 * @brief Implementation of a factory pattern that dynamically allocates
 *        the appropriate ExpressionTreeIteratorImpl object.
 *
 *        This is a variant of the Abstract Factory pattern that
 *        has a set of related factory methods but which doesn't use
 *        inheritance.
 *
 * @see   ExpressionTreeLevelOrderIteratorImpl,
 *        ExpressionTreeInOrderIteratorImpl,
 *        ExpressionTreePreOrderIteratorImpl, and
 *        ExpressionTreePostOrderIteratorImpl.
 */
class ExpressionTreeIteratorFactory {
public:
    // Constructor.
    ExpressionTreeIteratorFactory();

    // Dynamically allocate a new ExpressionTreeIteratorImpl
    // object based on the designated traversalOrder and endIter.
    ExpressionTreeIteratorImpl* makeTreeIterator(
        ExpressionTree& tree, const std::string& traversalOrder, bool endIter);

private:
    // Dynamically allocate a new ExpressionTreeLevelOrderIteratorImpl
    // object based on the designated end_iter.
    ExpressionTreeIteratorImpl* makeInOrderTreeIterator(ExpressionTree& tree, bool endIter);

    // Dynamically allocate a new ExpressionTreePreOrderIteratorImpl
    // object based on the designated endIter.
    ExpressionTreeIteratorImpl* makePreOrderTreeIterator(ExpressionTree& tree, bool endIter);

    // Dynamically allocate a new ExpressionTreePostOrderIteratorImpl
    // object based on the designated endIter.
    ExpressionTreeIteratorImpl* makePostOrderTreeIterator(ExpressionTree& tree, bool endIter);

    // Dynamically allocate a new ExpressionTreeLevelOrderIteratorImpl
    // object based on the designated endIter.
    ExpressionTreeIteratorImpl* makeLevelOrderTreeIterator(ExpressionTree& tree, bool endIter);

    typedef ExpressionTreeIteratorImpl* (ExpressionTreeIteratorFactory::*TRAVERSAL_PTMF)(
        ExpressionTree& tree, bool endIter);

    typedef std::map<std::string, TRAVERSAL_PTMF> TRAVERSAL_MAP;

    TRAVERSAL_MAP traversalMap;
};

ExpressionTreeIteratorFactory::ExpressionTreeIteratorFactory()
{
    traversalMap["in-order"] = &ExpressionTreeIteratorFactory::makeInOrderTreeIterator;
    traversalMap["pre-order"] = &ExpressionTreeIteratorFactory::makePreOrderTreeIterator;
    traversalMap["post-order"] = &ExpressionTreeIteratorFactory::makePostOrderTreeIterator;
    traversalMap["level-order"] = &ExpressionTreeIteratorFactory::makeLevelOrderTreeIterator;
}

ExpressionTreeIteratorImpl* ExpressionTreeIteratorFactory::makeLevelOrderTreeIterator(
    ExpressionTree& tree, bool endIter)
{
    return new LevelOrderExpressionTreeIteratorImpl(tree, endIter);
}

ExpressionTreeIteratorImpl* ExpressionTreeIteratorFactory::makeInOrderTreeIterator(
    ExpressionTree& tree, bool endIter)
{
    return new InOrderExpressionTreeIteratorImpl(tree, endIter);
}

ExpressionTreeIteratorImpl* ExpressionTreeIteratorFactory::makePreOrderTreeIterator(
    ExpressionTree& tree, bool endIter)
{
    return new PreOrderExpressionTreeIteratorImpl(tree, endIter);
}

ExpressionTreeIteratorImpl* ExpressionTreeIteratorFactory::makePostOrderTreeIterator(
    ExpressionTree& tree, bool endIter)
{
    return new PostOrderExpressionTreeIteratorImpl(tree, endIter);
}

ExpressionTreeIteratorImpl* ExpressionTreeIteratorFactory::makeTreeIterator(
    ExpressionTree& tree, const std::string& traversalOrder, bool endIter)
{
    auto iter = traversalMap.find(traversalOrder);
    if (iter == traversalMap.end()) {
        // We don't understand the type. Convert the type to a string
        // and pass it back via an exception

        throw ExpressionTree::InvalidIterator(traversalOrder);
    } else {
        auto ptmf = iter->second;
        return (this->*ptmf)(tree, endIter);
    }
}

// Define a single instance of a factory that's local to this class.
static ExpressionTreeIteratorFactory treeIteratorFactory;

// Default ctor
ExpressionTree::ExpressionTree()
    : root(nullptr)
{
}

// Ctor take an underlying NODE*.
ExpressionTree::ExpressionTree(ComponentNode* inRoot, const bool increment)
    : root(inRoot, increment)
{
}

// Copy ctor
ExpressionTree::ExpressionTree(const ExpressionTree& rhs)
    : root(rhs.root)
{
}

// Assignment operator
ExpressionTree& ExpressionTree::operator=(const ExpressionTree& rhs)
{
    // Refcounter class takes care of the internal decrements and
    // increments.
    if (this != &rhs)
        root = rhs.root;
    return *this;
}

bool ExpressionTree::operator==(const ExpressionTree& rhs) const
{
    return root.get_ptr() == rhs.root.get_ptr();
}

// Check if the tree is empty.
bool ExpressionTree::isNull() const
{
    return root.get_ptr() == nullptr;
}

// return root pointer
ComponentNode* ExpressionTree::getRoot()
{
    return root.get_ptr();
}

// Return the stored item.
int ExpressionTree::item() const
{
    return root->item();
}

// Return the left branch.
ExpressionTree ExpressionTree::left()
{
    return ExpressionTree(root->left(), true);
}

// Return the left branch.
ExpressionTree ExpressionTree::right()
{
    auto rt = root->right();
    return ExpressionTree(rt, true);
}

// Return a begin iterator of a specified type.
ExpressionTree::iterator ExpressionTree::begin(const std::string& traversalOrder)
{
    /*
    if (traversal_order == "Pre-order")
      return Express_Tree_Iterator (new Pre_Order_Tree_Iterator_Impl (*this,
    false));
    else if (traversal_order == "Level-order")
      return Express_Tree_Iterator (new Level_Order_Tree_Iterator_Impl (*this,
    false));
    */
    return ExpressionTree::iterator(
        treeIteratorFactory.makeTreeIterator(*this, traversalOrder, false));
}

// Return an end iterator of a specified type.
ExpressionTree::iterator ExpressionTree::end(const std::string& traversal_order)
{
    return ExpressionTree::iterator(
        treeIteratorFactory.makeTreeIterator(*this, traversal_order, true));
}

// Return a begin iterator of a specified type.
ExpressionTreeConstIterator ExpressionTree::begin(const std::string& traversal_order) const
{
    ExpressionTree* nonConstThis = const_cast<ExpressionTree*>(this);
    return ExpressionTree::const_iterator(
        treeIteratorFactory.makeTreeIterator(*nonConstThis, traversal_order, false));
}

// Return an end iterator of a specified type.
ExpressionTreeConstIterator ExpressionTree::end(const std::string& traversal_order) const
{
    ExpressionTree* nonConstThis = const_cast<ExpressionTree*>(this);
    return ExpressionTree::const_iterator(
        treeIteratorFactory.makeTreeIterator(*nonConstThis, traversal_order, true));
}

// Accept a visitor to perform some action on the Expression_Tree.
void ExpressionTree::accept(Visitor& visitor) const
{
    root->accept(visitor);
}
