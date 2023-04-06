/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "interpreter/symbol.h"
#include "tree/add_node.h"
#include "tree/ceiling_node.h"
#include "tree/divide_node.h"
#include "tree/exponent_node.h"
#include "tree/factorial_node.h"
#include "tree/floor_node.h"
#include "tree/leaf_node.h"
#include "tree/modulus_node.h"
#include "tree/multiply_node.h"
#include "tree/negate_node.h"
#include "tree/subtract_node.h"
#include <cstdlib>
#include <memory>

// constructor
Symbol::Symbol(Symbol* l, Symbol* r, int precedence)
    : left(l)
    , right(r)
    , prec(precedence)
{
}

// destructor
Symbol::~Symbol()
{
    delete left;
    delete right;
}

// constructor
Operator::Operator(Symbol* left, Symbol* right, int precedence)
    : Symbol(left, right, precedence)
{
}

// constructor
UnaryOperator::UnaryOperator(Symbol* right, int precedence)
    : Symbol(nullptr, right, precedence)
{
}

// constructor
LeftUnaryOperator::LeftUnaryOperator(Symbol* left, int precedence)
    : Symbol(left, nullptr, precedence)
{
}
// constructor
Number::Number(const std::string& input)
    : Symbol(nullptr, nullptr, 6)
{
    item = ::atoi(input.c_str());
}

// constructor
Number::Number(const int& input)
    : Symbol(nullptr, nullptr, 6)
    , item(input)
{
}

// returns the precedence level
int Number::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 6 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Number::build()
{
    return new LeafNode(item);
}

// constructor
Negate::Negate()
    : UnaryOperator(nullptr, 3)
{
}

// returns the precedence level
int Negate::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 3 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Negate::build()
{
    if (right == nullptr) {
        throw(std::invalid_argument("Required operands not given"));
    }
    return new NegateNode(right->build());
}

// constructor
Add::Add()
    : Operator(nullptr, nullptr, 1)
{
}

// returns the precedence level
int Add::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 1 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Add::build()
{
    if (left == nullptr || right == nullptr) {
        throw(std::invalid_argument("Required operands not given"));
    }
    return new AddNode(left->build(), right->build());
}

// constructor
Subtract::Subtract()
    : Operator(nullptr, nullptr, 1)
{
}

// returns the precedence level
int Subtract::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 1 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Subtract::build()
{
    if (left == nullptr || right == nullptr) {
        throw(std::invalid_argument("Required operands not given"));
    }
    return new SubtractNode(left->build(), right->build());
}

// constructor
Multiply::Multiply()
    : Operator(nullptr, nullptr, 2)
{
}

// returns the precedence level
int Multiply::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 2 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Multiply::build()
{
    if (left == nullptr || right == nullptr) {
        throw(std::invalid_argument("Required operands not given"));
    }
    return new MultiplyNode(left->build(), right->build());
}

// constructor
Divide::Divide()
    : Operator(nullptr, nullptr, 2)
{
}

// returns the precedence level
int Divide::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 2 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Divide::build()
{
    if (left == nullptr || right == nullptr) {
        throw(std::invalid_argument("Required operands not given"));
    }
    return new DivideNode(left->build(), right->build());
}

// constructor
Exponent::Exponent()
    : Operator(nullptr, nullptr, 4)
{
}

// returns the precedence level
int Exponent::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 4 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Exponent::build()
{
    if (left == nullptr || right == nullptr) {
        throw(std::invalid_argument("Required operands not given"));
    }
    return new ExponentNode(left->build(), right->build());
}

// constructor
Modulus::Modulus()
    : Operator(nullptr, nullptr, 2)
{
}

// returns the precedence level
int Modulus::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 2 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Modulus::build()
{
    if (left == nullptr || right == nullptr) {
        throw(std::invalid_argument("Required operands not given"));
    }
    return new ModulusNode(left->build(), right->build());
}

// constructor
Factorial::Factorial()
    : LeftUnaryOperator(nullptr, 5)
{
}

// returns the precedence level
int Factorial::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 5 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Factorial::build()
{
    if (left == nullptr) {
        throw(std::invalid_argument("Required operands not given"));
    }
    return new FactorialNode(left->build());
}

Ceiling::Ceiling()
    : Operator(nullptr, nullptr, 2)
{
}

// returns the precedence level
int Ceiling::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 2 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Ceiling::build()
{
    if (left == nullptr || right == nullptr) {
        throw(std::invalid_argument("Required operands not given"));
    }
    return new CeilingNode(left->build(), right->build());
}

Floor::Floor()
    : Operator(nullptr, nullptr, 2)
{
}

// returns the precedence level
int Floor::addPrecedence(int accumulatedPrecedence)
{
    return this->prec = 2 + accumulatedPrecedence;
}

// builds an equivalent Expression_Tree node
ComponentNode* Floor::build()
{
    if (left == nullptr || right == nullptr) {
        throw(std::invalid_argument("Required operands not given"));
    }
    return new FloorNode(left->build(), right->build());
}