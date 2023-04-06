/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "core/context.h"
#include <algorithm>

Context::Context(std::ostream& os)
    : treeState(new UninitializedState(*this))
    , isFormatted(false)
    , os(os)
{
}

void Context::format(const std::string& newFormat)
{
    treeState->format(newFormat);
    // we only reach here if the format was successful, and once
    // this is set, we will always have at least one valid format
    // because we store the last valid command (which would have
    // a valid format, if this format function has ever been successfully ran
    isFormatted = true;
    addCommand("format " + newFormat);
}

void Context::makeTree(const std::string& expression)
{
    treeState->makeTree(expression);
    addCommand("expr " + expression);
}

void Context::print(const std::string& format)
{
    treeState->print(format, os);
    addCommand("print " + format);
}

int Context::evaluate(const std::string& format)
{
    auto tmp = treeState->evaluate(format);
    addCommand("eval " + format);
    return tmp;
}

void Context::set(const std::string& kvPair)
{
    std::string input = kvPair;
    // used for keeping track of found characters
    std::string::size_type pos;
    // get rid of all spaces
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

    // input should be key=value
    if ((pos = input.find('=')) != std::string::npos) {
        // if the position is not the first char (eg '=value')
        // and position is not the last char (eg 'key=')
        // then split the string and set the interpreter context
        // accordingly
        if (pos != 0 && pos < input.length() - 1) {
            std::string key = input.substr(0, pos);
            std::string value = input.substr(pos + 1);

            variables.set(key, atoi(value.c_str()));
        } else
            throw std::domain_error("Must be in the form key=value");
    } else
        throw std::domain_error("Must have = sign present");

    addCommand("set " + kvPair);
}

void Context::get(const std::string& var)
{
    os << variables.get(var) << std::endl;
    addCommand("get " + var);
}

void Context::list()
{
    variables.print(os);
    os << std::endl;
    addCommand("list");
}

State* Context::state() const
{
    return treeState.get();
}

void Context::state(State* state)
{
    treeState.reset(state);
}

ExpressionTree& Context::tree()
{
    return expTree;
}

void Context::tree(const ExpressionTree& tree)
{
    expTree = tree;
}

VariableMap& Context::getVariables()
{
    return variables;
}

bool Context::formatted() const
{
    return isFormatted;
}

std::ostream& Context::output() const
{
    return os;
}

std::queue<std::string> Context::getHistory()
{
    return historyQ;
}

void Context::history()
{
    for (uint32_t i = 1; i < historyQ.size() + 1; ++i) {
        auto tmp = historyQ.front();
        os << i << ") " << tmp << std::endl;
        historyQ.pop();
        historyQ.push(tmp);
    }
}

void Context::addCommand(std::string input)
{
    if (historyQ.size() == 5) {
        historyQ.pop();
    }
    historyQ.push(input);
}