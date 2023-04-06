/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef SET_COMMAND_H
#define SET_COMMAND_H

#include "commands/command_impl.h"
#include <string>

/**
 * @class SetCommand
 * @brief Sets a variable into the VariableMap stored inside of Context.
 */
class SetCommand : public Command_Impl {
public:
    // Constructor that provides the Context and the k-v pair.
    SetCommand(Context& context, std::string);
    // Evaluate the expression tree.
    bool execute() override;

private:
    // Format to use for the evaluation.
    std::string pair;
};

#endif // SET_COMMAND_H
