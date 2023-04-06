/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "interpreter/interpreter.h"
#include "interpreter/symbol.h"
#include "interpreter/variable_map.h"
#include <memory>

// method for checking if a character is a valid operator
[[maybe_unused]] bool Interpreter::isOperator(char input)
{
    return input == '+' || input == '-' || input == '*' || input == '/' || input == '^'
        || input == '%' || input == '!' || input == '|' || input == '_';
}

// method for checking if a character is a number
bool Interpreter::isNumber(char input)
{
    return input >= '0' && input <= '9';
}

// method for checking if a character is a candidate
// for a part of a variable name
bool Interpreter::isAlphanumeric(char input)
{
    return (input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z')
        || (input >= '0' && input <= '9');
}

// inserts a terminal into the parse tree
[[maybe_unused]] void Interpreter::terminalInsert(Symbol* terminal, std::list<Symbol*>& list)
{
    if (!list.empty()) {
        // Something exists in the list, so make this number the rightmost child

        Symbol* symbol = list.back();

        if (symbol) {
            // while there is a right child, continue down
            for (; symbol->right; symbol = symbol->right)
                continue;

            // symbol right will be this terminal and that's all we have
            // to do.
            symbol->right = terminal;
        }
    } else
        // a number appeared first
        list.push_back(terminal);
}

// inserts a variable (leaf node / number) into the parse tree
void Interpreter::variableInsert(const VariableMap& vars, const std::string& input,
    std::string::size_type& i, int& accumulatedPrecedence, std::list<Symbol*>& list,
    Symbol*& lastValidInput)
{
    // merge all consecutive number chars into a single
    // Number symbol, eg '123' = int (123). Scope of j needs
    // to be outside of the for loop.

    std::string::size_type j = 1;

    for (; i + j <= input.length() && isAlphanumeric(input[i + j]); ++j)
        continue;

    // lookup the variable in the context

    int value = vars.get(input.substr(i, j));

    // make a Number out of the integer

    auto number = new Number(value);
    number->addPrecedence(accumulatedPrecedence);

    lastValidInput = number;

    // update i to the last character that was a number. the ++i will
    // update the i at the end of the loop to the next check.

    i += j - 1;

    precedenceInsert(number, list);
}

// inserts a leaf node / number into the parse tree
void Interpreter::numberInsert(const std::string& input, std::string::size_type& i,
    int& accumulatedPrecedence, std::list<Symbol*>& list, Symbol*& lastValidInput)
{
    // merge all consecutive number chars into a single Number symbol,
    // eg '123' = int (123). Scope of j needs to be outside of the for
    // loop.

    std::string::size_type j = 1;

    for (; i + j <= input.length() && isNumber(input[i + j]); ++j)
        continue;

    auto number = new Number(input.substr(i, j));
    number->addPrecedence(accumulatedPrecedence);

    lastValidInput = number;

    // update i to the last character that was a number. the ++i will
    // update the i at the end of the loop to the next check.

    i += j - 1;

    precedenceInsert(number, list);
}

// inserts a multiplication or division into the parse tree
void Interpreter::precedenceInsert(Symbol* op, std::list<Symbol*>& list)
{
    if (!list.empty()) {
        // if last element was a number, then make that our left_

        Symbol* parent = list.back();
        Symbol* child = parent->right;

        if (child) {
            // while there is a child of parent, keep going down the right side
            for (; child && child->precedence() < op->precedence(); child = child->right)
                parent = child;
        }

        if (parent->precedence() < op->precedence()) {

            // op left will be the old child. new parent child will be
            // the op. To allow infinite negations, we have to check for
            // unary_operator.

            // **************** This is the culprit

            if (!op->left)
                op->left = child;

            parent->right = op;
        } else {
            // this can be one of two things, either we are the same
            // precedence or we are less precedence than the parent.
            // this also means different things for unary ops. The
            // most recent unary op (negate) has a higher precedence

            if (dynamic_cast<UnaryOperator*>(op)) {
                for (; child && child->precedence() == op->precedence(); child = child->right)
                    parent = child;

                // I can't think of a valid reason that parent->right would
                // be possible !0

                parent->right = op;
            } else {
                // everything else is evaluated the same. For instance, if
                // this is 5 * 4 / 2, and we currently have Mult (5,4) in the
                // list, we need to make parent our left child.

                op->left = parent;
                list.pop_back();
                list.push_back(op);
            }
        }
    } else {
        list.push_back(op);
    }
}

void Interpreter::mainLoop(const VariableMap& vars, const std::string& input,
    std::string::size_type& i, Symbol*& lastValidInput, bool& handled, int& accumulatedPrecedence,
    std::list<Symbol*>& list)
{
    handled = false;
    if (isNumber(input[i])) {
        handled = true;
        // leaf node
        numberInsert(input, i, accumulatedPrecedence, list, lastValidInput);
    } else if (isAlphanumeric(input[i])) {
        handled = true;
        // variable leaf node
        variableInsert(vars, input, i, accumulatedPrecedence, list, lastValidInput);
    } else if (input[i] == '+') {
        handled = true;
        // addition operation
        auto op = new Add();
        op->addPrecedence(accumulatedPrecedence);

        lastValidInput = nullptr;

        // insert the op according to left-to-right relationships
        precedenceInsert(op, list);
    } else if (input[i] == '-') {
        handled = true;

        Symbol* op;
        if (!lastValidInput) {
            // Negate
            op = new Negate();
            op->addPrecedence(accumulatedPrecedence);
        } else {
            // Subtract
            op = new Subtract();
            op->addPrecedence(accumulatedPrecedence);
        }

        lastValidInput = nullptr;

        // insert the op according to left-to-right relationships
        precedenceInsert(op, list);

    } else if (input[i] == '*') {
        handled = true;
        // multiplication operation
        auto op = new Multiply();
        op->addPrecedence(accumulatedPrecedence);

        lastValidInput = nullptr;

        // insert the op according to precedence relationships
        precedenceInsert(op, list);
        // associative_insert (op);
    } else if (input[i] == '/') {
        handled = true;
        // division operation
        auto op = new Divide();
        op->addPrecedence(accumulatedPrecedence);

        lastValidInput = nullptr;

        // insert the op according to precedence relationships
        precedenceInsert(op, list);

    } else if (input[i] == '|') {
        handled = true;
        // modulus operation
        auto op = new Ceiling();
        op->addPrecedence(accumulatedPrecedence);

        lastValidInput = nullptr;

        // insert the op according to precedence relationships
        precedenceInsert(op, list);

    } else if (input[i] == '_') {
        handled = true;
        // modulus operation
        auto op = new Floor();
        op->addPrecedence(accumulatedPrecedence);

        lastValidInput = nullptr;

        // insert the op according to precedence relationships
        precedenceInsert(op, list);

    } else if (input[i] == '%') {
        handled = true;
        // modulus operation
        auto op = new Modulus();
        op->addPrecedence(accumulatedPrecedence);

        lastValidInput = nullptr;

        // insert the op according to precedence relationships
        precedenceInsert(op, list);
    } else if (input[i] == '^') {
        handled = true;
        // exponent operation
        auto op = new Exponent();
        op->addPrecedence(accumulatedPrecedence);

        lastValidInput = nullptr;

        // insert the op according to precedence relationships
        precedenceInsert(op, list);

    } else if (input[i] == '!') {
        handled = true;
        // factorial operation
        auto op = new Factorial();
        op->addPrecedence(accumulatedPrecedence);

        // insert the op according to precedence relationships
        precedenceInsert(op, list);

    } else if (input[i] == '(') {
        handled = true;
        handleParenthesis(vars, input, i, lastValidInput, handled, accumulatedPrecedence, list);
    } else if (input[i] == ' ' || input[i] == '\n') {
        handled = true;
        // skip whitespace
    }
}

void Interpreter::handleParenthesis(const VariableMap& vars, const std::string& input,
    std::string::size_type& i, Symbol*& lastValidInput, bool& handled, int& accumulatedPrecedence,
    std::list<Symbol*>& master_list)
{
    /* handle parenthesis is a lot like handling a new interpret.
       the difference is that we have to worry about how the calling
       function has its list setup */
    // std::cerr << "Handling an opening parenthesis.\n";

    accumulatedPrecedence += 5;
    std::list<Symbol*> list;
    handled = false;
    for (++i; i < input.length(); ++i) {
        mainLoop(vars, input, i, lastValidInput, handled, accumulatedPrecedence, list);
        if (input[i] == ')') {
            // std::cerr << "Handling a closing parenthesis.\n";
            handled = true;
            //++i;
            accumulatedPrecedence -= 5;
            break;
        }
    }

    if (!master_list.empty() && !list.empty()) {
        Symbol* lastSymbol = master_list.back();
        auto op = dynamic_cast<Operator*>(lastSymbol);
        auto unary = dynamic_cast<UnaryOperator*>(lastSymbol);

        // is it a node with 2 children?
        if (op) {
            precedenceInsert(list.back(), master_list);
        } else if (unary)
        // is it a unary node (like negate)
        {
            precedenceInsert(list.back(), master_list);
        } else {
            // is it a terminal node (Number)
            // error
        }
    } else if (!list.empty())
        master_list = list;

    list.clear();
}

// Converts a string and context into a parse tree and builds an
// expression tree out of the parse tree.

ExpressionTree Interpreter::interpret(const VariableMap& vars, const std::string& input)
{
    std::list<Symbol*> list;
    // list.clear ();
    Symbol* lastValidInput = nullptr;
    bool handled = false;
    int accumulatedPrecedence = 0;

    for (std::string::size_type i = 0; i < input.length(); ++i) {
        mainLoop(vars, input, i, lastValidInput, handled, accumulatedPrecedence, list);
    }

    // if the list has an element in it, then return the back of the list.
    if (!list.empty()) {
        // Invoke a recursive ExpressionTree build starting with the
        // root symbol. This is an example of the builder pattern. See
        // pg 97 in GoF book.
        ExpressionTree tree = ExpressionTree(list.back()->build());
        delete list.back();
        return tree;
    }

    // If we reach this, we didn't have any symbols.
    return {};
}
