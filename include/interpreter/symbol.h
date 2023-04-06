/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

// Class Predeclarations
class ComponentNode;

/**
 * @class Symbol
 * @brief Abstract base class of all parse tree nodes.
 */
class Symbol {
public:
    // constructor
    Symbol(Symbol* l, Symbol* r, int precedence = 0);
    // destructor
    virtual ~Symbol();
    // abstract method for returning precedence level (higher
    // value means higher precedence
    virtual int precedence()
    {
        return prec;
    }
    virtual int addPrecedence(int accumulatedPrecedence) = 0;
    // abstract method for building an Expression ExpressionTree Node
    virtual ComponentNode* build() = 0;
    // left and right pointers
    Symbol* left;
    Symbol* right;
    int prec;
};

/**
 * @class Operator
 * @brief Abstract base class for all parse tree node operators
 * @see   Add, Subtract, Multiply, Divide
 */
class Operator : public Symbol {
public:
    // constructor
    Operator(Symbol* left, Symbol* right, int precedence = 1);
    // destructor
    ~Operator() override = default;
};

/**
 * @class UnaryOperator
 * @brief Abstract base class for all parse tree node operators
 * @see   Add, Subtract, Multiply, Divide
 */
class UnaryOperator : public Symbol {
public:
    // constructor
    explicit UnaryOperator(Symbol* right, int precedence = 1);
    // destructor
    ~UnaryOperator() override = default;
};

/**
 * @class LeftUnaryOperator
 * @brief Abstract base class for all parse tree node operators
 * @see   Add, Subtract, Multiply, Divide
 */
class LeftUnaryOperator : public Symbol {
public:
    // constructor
    explicit LeftUnaryOperator(Symbol* left, int precedence = 1);
    // destructor
    ~LeftUnaryOperator() override = default;
};

/**
 * @class Number
 * @brief Leaf node of parse tree
 */
class Number : public Symbol {
public:
    // constructors
    explicit Number(const std::string& input);
    explicit Number(const int& input);
    // destructor
    ~Number() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent ExpressionTree node
    ComponentNode* build() override;

private:
    // contains the value of the leaf node
    int item;
};

/**
 * @class Subtract
 * @brief Subtraction node of the parse tree
 */
class Subtract : public Operator {
public:
    // constructor
    Subtract();
    // destructor
    ~Subtract() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent ExpressionTree node
    ComponentNode* build() override;
};

/**
 * @class Add
 * @brief Addition node of the parse tree
 */
class Add : public Operator {
public:
    // constructor
    Add();
    // destructor
    ~Add() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent Expression_Tree node
    ComponentNode* build() override;
};

/**
 * @class Negate
 * @brief Negate node of the parse tree
 */
class Negate : public UnaryOperator {
public:
    // constructor
    Negate();
    // destructor
    ~Negate() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent ExpressionTree node
    ComponentNode* build() override;
};

/**
 * @class Multiply
 * @brief Multiplication node of the parse tree
 */
class Multiply : public Operator {
public:
    // constructor
    Multiply();
    // destructor
    ~Multiply() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent Expression_Tree node
    ComponentNode* build() override;
};

/**
 * @class Divide
 * @brief Division node of the parse tree
 */
class Divide : public Operator {
public:
    // constructor
    Divide();
    // destructor
    ~Divide() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent Expression_Tree node
    ComponentNode* build() override;
};

class Exponent : public Operator {
public:
    // constructor
    Exponent();
    // destructor
    ~Exponent() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent Expression_Tree node
    ComponentNode* build() override;
};

class Modulus : public Operator {
public:
    // constructor
    Modulus();
    // destructor
    ~Modulus() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent Expression_Tree node
    ComponentNode* build() override;
};

class Factorial : public LeftUnaryOperator {
public:
    // constructor
    Factorial();
    // destructor
    ~Factorial() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent ExpressionTree node
    ComponentNode* build() override;
};

class Ceiling : public Operator {
public:
    // constructor
    Ceiling();
    // destructor
    ~Ceiling() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent Expression_Tree node
    ComponentNode* build() override;
};

class Floor : public Operator {
public:
    // constructor
    Floor();
    // destructor
    ~Floor() override = default;
    // returns the precedence level
    int addPrecedence(int accumulatedPrecedence) override;
    // builds an equivalent Expression_Tree node
    ComponentNode* build() override;
};

#endif // SYMBOL_H
