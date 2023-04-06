/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef COMMAND_IMPL_H
#define COMMAND_IMPL_H

// Forward declarations.
class Context;

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
class Command_Impl {
public:
    // Constructor that provides the appropriate Context.
    explicit Command_Impl(Context&);
    // Destructor.
    virtual ~Command_Impl() = default;

    // Pure virtual method for executing a command that must be defined by subclasses.
    virtual bool execute() = 0;

protected:
    // Reference to the Context that's the target of the command.
    Context& context;
};

#endif // COMMAND_IMPL_H
