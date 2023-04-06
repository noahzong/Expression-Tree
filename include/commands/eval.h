/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef EVAL_COMMAND_H
#define EVAL_COMMAND_H

#include "commands/command_impl.h"
#include <string>

/**
 * @class EvalCommand
 * @brief Evaluates the expression tree in the desired format, e.g., "in-order," "pre-order,"
 * "post-order", or "level-order".
 */
class EvalCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context and the requested format.
    EvalCommand(Context&, std::string);

    // Evaluate the expression tree.
    bool execute() override;

private:
    // Format to use for the evaluation.
    std::string format;
};

#endif // EVAL_COMMAND_H
