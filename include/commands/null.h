/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef NULL_COMMAND_H
#define NULL_COMMAND_H

#include "commands/command_impl.h"

/**
 * @class NullCommand
 * @brief No-op command
 */
class NullCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context and the requested format.
    explicit NullCommand(Context& context);

    // Set the desired format.
    bool execute() override;
};

#endif // NULL_COMMAND_H
