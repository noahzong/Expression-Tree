/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "core/context.h"
#include "interpreter/interpreter.h"
#include "tree/expression_tree_iterator.h"
#include "visitors/evaluation.h"
#include "visitors/print.h"
#include <algorithm>
#include <iostream>
#include <stdexcept>

// this method traverses the tree in with a given traversal strategy
void State::printTree(const ExpressionTree& tree, const std::string& order, std::ostream& os)
{
    // create a print visitor & traverse in order
    PrintVisitor visitor(os);
    std::for_each(
        tree.begin(order), tree.end(order), [&visitor](auto node) { node.accept(visitor); });
}

auto State::evaluateTree(const ExpressionTree& tree, const std::string& order)
{
    EvaluationVisitor visitor;
    std::for_each(
        tree.begin(order), tree.end(order), [&visitor](auto node) { node.accept(visitor); });
    return visitor.total();
}

// Static data member definitions.
UninitializedState::UninitializedStateFactory::UNINITIALIZED_STATE_MAP
    UninitializedState::UninitializedStateFactory::uninitializedStateMap;

UninitializedState::UninitializedStateFactory UninitializedState::uninitializedStateFactory;

UninitializedState::UninitializedStateFactory::UninitializedStateFactory()
{
    uninitializedStateMap["in-order"]
        = &UninitializedState::UninitializedStateFactory::makeInOrderUninitializedState;
    uninitializedStateMap["pre-order"]
        = &UninitializedState::UninitializedStateFactory::makePreOrderUninitializedState;
    uninitializedStateMap["post-order"]
        = &UninitializedState::UninitializedStateFactory::makePostOrderUninitializedState;
    uninitializedStateMap["level-order"]
        = &UninitializedState::UninitializedStateFactory::makeLevelOrderUninitializedState;
}

State* UninitializedState::UninitializedStateFactory::makeLevelOrderUninitializedState(
    Context& context)
{
    return new LevelOrderUninitializedState(context);
}

State* UninitializedState::UninitializedStateFactory::makeInOrderUninitializedState(
    Context& context)
{
    return new InOrderUninitializedState(context);
}

State* UninitializedState::UninitializedStateFactory::makePreOrderUninitializedState(
    Context& context)
{
    return new PreOrderUninitializedState(context);
}

State* UninitializedState::UninitializedStateFactory::makePostOrderUninitializedState(
    Context& context)
{
    return new PostOrderUninitializedState(context);
}

State* UninitializedState::UninitializedStateFactory::makeUninitializedState(
    Context& context, const std::string& format)
{
    auto iter = uninitializedStateMap.find(format);
    if (iter == uninitializedStateMap.end()) {
        // We don't understand the type. Convert the type to a string
        // and pass it back via an exception
        throw ExpressionTree::InvalidIterator(format);
    } else {
        UninitializedState::UninitializedStateFactory::UNINITIALIZED_STATE_PTF ptf = iter->second;
        return (*ptf)(context);
    }
}

UninitializedState::UninitializedState(Context& ctx)
    : State(ctx) {};

void UninitializedState::format(const std::string& format)
{
    // Call factory method to initialize the context state.
    context.state(UninitializedStateFactory::makeUninitializedState(context, format));
}

void UninitializedState::makeTree(const std::string&)
{
    throw State::InvalidState("Expr - Can't call that command yet.");
}

void UninitializedState::print(const std::string&, std::ostream&)
{
    throw State::InvalidState("Print - Can't call that command yet.");
}

int UninitializedState::evaluate(const std::string&)
{
    throw State::InvalidState("Eval - Can't call that command yet.");
}

void UninitializedState::printValidCommands() const
{
    auto& os = context.output();
    os << "1a. format [in-order]\n";
    os << "1b. set [variable=value]\n";
    if (!context.getVariables().isEmpty()) {
        os << "1c. get [variable]\n";
        os << "1d. list \n";
    }
    if (!context.getHistory().empty()) {
        os << "1e. history \n";
    }
    os << "2. expr [expression]\n";
    os << "3a. eval [post-order]\n";
    os << "3b. print [in-order | pre-order | post-order | level-order]\n";
    os << "0. quit\n";
    os.flush();
}

PreOrderUninitializedState::PreOrderUninitializedState(Context& ctx)
    : UninitializedState(ctx)
{
}

void PreOrderUninitializedState::makeTree(const std::string&)
{
    throw State::InvalidState("Pre_Order_Uninitialized_State::make_tree - not implemented");
}

void PreOrderInitializedState::print(const std::string& format, std::ostream& os)
{
    State::printTree(context.tree(), format, os);
}

int PreOrderInitializedState::evaluate(const std::string& param)
{
    return State::evaluateTree(context.tree(), param);
}

PostOrderUninitializedState::PostOrderUninitializedState(Context& ctx)
    : UninitializedState(ctx)
{
}

void PostOrderUninitializedState::makeTree(const std::string&)
{
    throw State::InvalidState("Post_Order_Uninitialized_State::make_tree - not implemented");
}

void PostOrderInitializedState::print(const std::string& format, std::ostream& os)
{
    return State::printTree(context.tree(), format, os);
}

int PostOrderInitializedState::evaluate(const std::string& param)
{
    return State::evaluateTree(context.tree(), param);
}

LevelOrderUninitializedState::LevelOrderUninitializedState(Context& ctx)
    : UninitializedState(ctx)
{
}

void LevelOrderUninitializedState::makeTree(const std::string&)
{
    throw State::InvalidState("LevelOrderUninitializedState::makeTree - not implemented");
}

void LevelOrderInitializedState::print(const std::string& format, std::ostream& os)
{
    State::printTree(context.tree(), format, os);
}

int LevelOrderInitializedState::evaluate(const std::string& param)
{
    return State::evaluateTree(context.tree(), param);
}

InOrderUninitializedState::InOrderUninitializedState(Context& ctx)
    : UninitializedState(ctx)
{
}

void InOrderUninitializedState::makeTree(const std::string& expr)
{
    context.tree(Interpreter::interpret(context.getVariables(), expr));
    context.state(new InOrderInitializedState(context));
}

void InOrderUninitializedState::printValidCommands() const
{
    auto& os = context.output();
    os << "1. expr [expression]\n";
    os << "2a. eval [post-order]\n";
    os << "2b. print [in-order | pre-order | post-order | level-order]\n";
    os << "0a. format [in-order]\n";
    os << "0b. set [variable=value]\n";
    if (!context.getVariables().isEmpty()) {
        os << "0c. get [variable]\n";
        os << "Od. list \n";
    }
    if (!context.getHistory().empty()) {
        os << "0e. history \n";
    }
    os << "0f. quit\n";
    os.flush();
}

InOrderInitializedState::InOrderInitializedState(Context& ctx)
    : InOrderUninitializedState(ctx)
{
}

void InOrderInitializedState::print(const std::string& format, std::ostream& os)
{
    State::printTree(context.tree(), format, os);
}

int InOrderInitializedState::evaluate(const std::string& param)
{
    return State::evaluateTree(context.tree(), param);
}

void InOrderInitializedState::printValidCommands() const
{
    auto& os = context.output();
    os << "1a. eval [post-order]\n";
    os << "1b. print [in-order | pre-order | post-order | level-order]\n";
    os << "0a. format [in-order]\n";
    os << "0b. set [variable=value]\n";
    if (!context.getVariables().isEmpty()) {
        os << "0c. get [variable]\n";
        os << "0d. list \n";
    }
    if (!context.getHistory().empty()) {
        os << "0e. history \n";
    }
    os << "0f. quit\n";
    os.flush();
}
