/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef PRINT_H
#define PRINT_H

#include "visitors/visitor.h"
#include <ostream>

/**
 * @class PrintVisitor
 * @brief This class serves as a visitor for printing the contents of
 *        nodes to output stream
 */

class PrintVisitor : public Visitor {
public:
    explicit PrintVisitor(std::ostream& os)
        : os(os)
    {
    }

    // Visits a LeafNode and prints it contents to output stream.
    void visit(const LeafNode& node) override;
    // Visit a NegateNode and prints its contents to output stream.
    void visit(const NegateNode& node) override;
    // Visit a AddNode and prints its contents to output stream.
    void visit(const AddNode& node) override;
    // Visit a SubtractNode and prints its contents to output stream.
    void visit(const SubtractNode& node) override;
    // Visit a DivideNode and prints its contents to output stream.
    void visit(const DivideNode& node) override;
    // visit function - prints MultiplyNode contents to output stream.
    void visit(const MultiplyNode& node) override;
    // visit function - prints ExponentNode contents to output stream.
    void visit(const ExponentNode& node) override;
    // visit function - prints ModulusNode contents to output stream.
    void visit(const ModulusNode& node) override;
    // visit function - prints FactorialNode contents to output stream.
    void visit(const FactorialNode& node) override;
    // visit function - prints CeilingNode contents to output stream.
    void visit(const CeilingNode& node) override;
    // visit function - prints FloorNode contents to output stream.
    void visit(const FloorNode& node) override;

private:
    std::ostream& os;
};

#endif // PRINT_H
