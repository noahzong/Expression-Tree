/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef QUIT_COMMAND_H
#define QUIT_COMMAND_H

#include "commands/command_impl.h"

/**
 * @class QuitCommand
 * @brief Instructs the event loop to shut down.
 */
class QuitCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context.
    explicit QuitCommand(Context&);

    // Quit the event loop.
    bool execute() override;
};

#endif // QUIT_COMMAND_H
