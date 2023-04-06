/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef COMMAND_H
#define COMMAND_H

#include <memory>

// Forward declarations.
class Command_Impl;

/**
 * @class Command
 * @brief Implementation of the Command pattern that is used to define a
 *        command performs an operation on the expression tree when
 *        executed.
 *
 *        Plays the role of the "implementor" base class in the Bridge
 *        pattern that is used as the basis for the subclasses that
 *        actually define the commands.
 */
class Command {
public:
    // Constructor that provides the appropriate Context.
    explicit Command(Command_Impl*);
    // Destructor.
    ~Command() = default;
    // Method for executing a command that must be defined by subclasses.
    bool execute();

protected:
    // Reference to the Context that's the target of the command.
    std::shared_ptr<Command_Impl> bridge;
};

#endif // COMMAND_H
