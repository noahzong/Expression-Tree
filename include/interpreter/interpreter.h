/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "tree/expression_tree.h"
#include <list>
#include <string>
#include <unordered_map>

// Forward declaration.
class Symbol;
class VariableMap;

/**
 * @class Interpreter
 * @brief Parses incoming expression strings into a parse tree and
 *        generates an expression tree from the parse tree.
 *
 *        This class plays the role of the "interpreter" in the
 *        Interpreter pattern.  It also uses the Builder pattern to
 *        generate the nodes in the expression tree.
 */
class Interpreter {
public:
    // Only static usage - no constructor.
    Interpreter() = delete;

    // Converts a string and variables into a parse tree, and builds an
    // expression tree out of the parse tree.
    static ExpressionTree interpret(const VariableMap& vars, const std::string& input);

private:
    // Method for checking if a character is a valid operator.
    [[maybe_unused]] static bool isOperator(char input);
    // Method for checking if a character is a number.
    static bool isNumber(char input);
    // Method for checking if a character is part of a variable name.
    static bool isAlphanumeric(char input);

    // Inserts a terminal into the parse tree.
    [[maybe_unused]] static void terminalInsert(Symbol* op, std::list<Symbol*>& list);
    // Inserts a variable (leaf node / number) into the parse tree.
    static void variableInsert(const VariableMap& varsa, const std::string& input,
        std::string::size_type& i, int& accumulated_precedence, std::list<Symbol*>& list,
        Symbol*& lastValidInput);
    // Inserts a leaf node / number into the parse tree.
    static void numberInsert(const std::string& input, std::string::size_type& i,
        int& accumulatedPrecedence, std::list<Symbol*>& list, Symbol*& lastValidInput);
    // Inserts a multiplication or division into the parse tree.
    static void precedenceInsert(Symbol* op, std::list<Symbol*>& list);
    // Process parenthesized expressions properly.
    static void handleParenthesis(const VariableMap& vars, const std::string& input,
        std::string::size_type& i, Symbol*& lastValidInput, bool& handled,
        int& accumulatedPrecedence, std::list<Symbol*>& list);

    // Main interpreter loop.
    static void mainLoop(const VariableMap&, const std::string&, std::string::size_type& i,
        Symbol*&, bool&, int&, std::list<Symbol*>&);
};

#endif // INTERPRETER_H
