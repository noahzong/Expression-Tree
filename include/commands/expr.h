/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef EXPR_COMMAND_H
#define EXPR_COMMAND_H

#include "commands/command_impl.h"
#include <string>

/**
 * @class ExprCommand
 * @brief Set the desired expression, e.g., "1+2*3".
 */
class ExprCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context and the requested expression.
    ExprCommand(Context&, std::string);

    // Create the desired expression tree.
    bool execute() override;

private:
    // Requested expression.
    std::string expression;
};

#endif // EXPR_COMMAND_H
