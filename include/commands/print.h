/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef PRINT_COMMAND_H
#define PRINT_COMMAND_H

#include "commands/command_impl.h"
#include <string>

/**
 * @class PrintCommand
 * @brief Prints the expression tree in the desired format, e.g., "in-order," "pre-order,"
 * "post-order", or "level-order".
 */
class PrintCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context and the requested format.
    PrintCommand(Context&, std::string);

    // Print the expression tree.
    bool execute() override;

private:
    // Format to print out the tree.
    std::string format;
};

#endif // PRINT_COMMAND_H
