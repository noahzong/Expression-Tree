/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef MACRO_COMMAND_H
#define MACRO_COMMAND_H

#include "commands/command.h"
#include "commands/command_impl.h"
#include <vector>

/**
 * @class MacroCommand
 * @brief Execute a sequence of commands.
 */
class MacroCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context and sequence of commands.
    MacroCommand(Context&, std::vector<Command>);

    // Default destructor
    ~MacroCommand() override = default;

    // Execute the sequence commands
    bool execute() override;

private:
    // Vector of commands that are executed as a macro.
    std::vector<Command> commands;
};

#endif // MACRO_COMMAND_H
