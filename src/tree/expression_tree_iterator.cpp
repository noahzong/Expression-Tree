/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "tree/expression_tree_iterator.h"
#include "tree/expression_tree.h"
#include "tree/expression_tree_iterator_impl.h"

// Copy ctor for impl *.
ExpressionTreeIterator::ExpressionTreeIterator(ExpressionTreeIteratorImpl* impl)
    : impl(impl)
{
}

// Dereference operator returns a reference to the item contained at
// the current position.
ExpressionTree ExpressionTreeIterator::operator*()
{
    // return impl_->operator*();
    return *(*impl);
}

// Returns a const reference to the item contained at the current position
const ExpressionTree ExpressionTreeIterator::operator*() const
{
    // return impl_->operator*();
    return *(*impl);
}

// Pre-increment operator
ExpressionTreeIterator& ExpressionTreeIterator::operator++()
{
    // return impl_->operator++ ();
    ++(*impl);
    return *this;
}

// Post-increment operator

const ExpressionTreeIterator ExpressionTreeIterator::operator++(int)
{
    ExpressionTreeIterator temp(impl->clone());
    // return impl_->operator++ ();
    ++(*impl);
    return temp;
}

// Equality operator

bool ExpressionTreeIterator::operator==(const ExpressionTreeIterator& rhs)
{
    // return impl_->operator () == rhs.impl_->operator ();
    return *impl == *rhs.impl;
}

// Nonequality operator

bool ExpressionTreeIterator::operator!=(const ExpressionTreeIterator& rhs)
{
    return !(*this == rhs);
}

// Copy ctor for impl *.
ExpressionTreeConstIterator::ExpressionTreeConstIterator(ExpressionTreeIteratorImpl* impl)
    : impl(impl)
{
}

// Returns a const reference to the item contained at the current position
const ExpressionTree ExpressionTreeConstIterator::operator*() const
{
    return *(*impl);
}

// Preincrement operator
ExpressionTreeConstIterator& ExpressionTreeConstIterator::operator++()
{
    ++(*impl);
    return *this;
}

// Preincrement operator
const ExpressionTreeConstIterator ExpressionTreeConstIterator::operator++(int)
{
    ExpressionTreeConstIterator temp(impl->clone());
    ++(*impl);
    return *this;
}

// Equality operator
bool ExpressionTreeConstIterator::operator==(const ExpressionTreeConstIterator& rhs)
{
    return impl->operator==(*rhs.impl);
}

// Nonequality operator
bool ExpressionTreeConstIterator::operator!=(const ExpressionTreeConstIterator& rhs)
{
    return !(*this == rhs);
}
