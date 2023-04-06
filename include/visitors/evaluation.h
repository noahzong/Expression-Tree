/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef EVALUATION_H
#define EVALUATION_H

#include "visitors/visitor.h"
#include <stack>

/**
 * @class EvaluationVisitor
 * @brief This plays the role of a visitor for evaluating
 *        nodes in an expression tree that is being iterated in
 *        post-order fashion (and does not work correctly with any
 *        other iterator).
 */
class EvaluationVisitor : public Visitor {
public:
    // Visit a LeafNode.
    void visit(const LeafNode& node) override;
    // Visit a NegateNode.
    void visit(const NegateNode& node) override;
    // Visit a AddNode.
    void visit(const AddNode& node) override;
    // Visit a SubtractNode.
    void visit(const SubtractNode& node) override;
    // Visit a DivideNode.
    void visit(const DivideNode& node) override;
    // Visit a MultiplyNode.
    void visit(const MultiplyNode& node) override;
    // Visit a ExponentNode.
    void visit(const ExponentNode& node) override;
    // Visit a ModulusNode.
    void visit(const ModulusNode& node) override;
    // Visit a FactorialNode.
    void visit(const FactorialNode& node) override;
    // Visit a CeilingNode.
    void visit(const CeilingNode& node) override;
    // Visit a FloorNode.
    void visit(const FloorNode& node) override;
    // Print the total of the evaluation.
    int total();
    // Resets the evaluation to it can be reused.
    void reset();

private:
    // Stack used for temporarily storing evaluations.
    std::stack<int> stack;
};

#endif // EVALUATION_H
