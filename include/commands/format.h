/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef FORMAT_COMMAND_H
#define FORMAT_COMMAND_H

#include "commands/command_impl.h"
#include <string>

/**
 * @class FormatCommand
 * @brief Set the desired format, e.g., "in-order," "pre-order," "post-order", or "level-order".
 */
class FormatCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context and the requested format.
    FormatCommand(Context&, std::string);

    // Set the desired format.
    bool execute() override;

private:
    // Requested format.
    std::string format;
};

#endif // FORMAT_COMMAND_H
