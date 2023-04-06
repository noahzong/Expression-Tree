/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "visitors/print.h"
#include "tree/leaf_node.h"

// visit function - prints LeafNode contents to output stream
void PrintVisitor::visit(const LeafNode& node)
{
    os << node.item() << " ";
}

// visit function - prints CompositeNegateNode contents to is
void PrintVisitor::visit(const NegateNode&)
{
    os << '-';
}

// visit function - prints AddNode contents to is
void PrintVisitor::visit(const AddNode&)
{
    os << "+ ";
}

// visit function - prints SubtractNode contents to is
void PrintVisitor::visit(const SubtractNode&)
{
    os << "- ";
}

// visit function - prints DivideNode contents to is
void PrintVisitor::visit(const DivideNode&)
{
    os << "/ ";
}

// visit function - prints MultiplyNode contents to is
void PrintVisitor::visit(const MultiplyNode&)
{
    os << "* ";
}

// visit function - prints ExponentNode contents to is
void PrintVisitor::visit(const ExponentNode&)
{
    os << "^ ";
}

// visit function - prints ModulusNode contents to is
void PrintVisitor::visit(const ModulusNode&)
{
    os << "% ";
}

void PrintVisitor::visit(const FactorialNode&)
{
    os << "! ";
}

void PrintVisitor::visit(const CeilingNode&)
{
    os << "| ";
}

void PrintVisitor::visit(const FloorNode&)
{
    os << "_ ";
}