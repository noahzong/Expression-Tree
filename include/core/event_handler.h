/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "commands/command.h"
#include "core/context.h"
#include "core/reactor.h"

class CommandFactory;

/**
 * @class EventHandler
 * @brief Provides an abstract interface for handling input events
 *        and commands associated with the expression tree application.
 *
 *        This class plays the role of "event handler" in the Reactor
 *        pattern and defines methods for use in the Template Method
 *        pattern that is used to process user input commands.
 *
 * @see   VerboseEventHandler and
 *        MacoEventHandler.
 */
class EventHandler : public Handler {
public:
    // Dtor.
    ~EventHandler() override = default;

    // Factory that creates the appropriate subclass of EventHandler, i.e.,
    // VerboseHandler or MacroHandler.
    static EventHandler* makeHandler(bool verbose, std::ostream&);

    // This method is called back by the reactor when input is
    // available.  It is a template method that performs the sequence
    // of steps associated with processing expression tree application
    // commands.
    void handle() override;

protected:
    // Constructor.
    explicit EventHandler(std::ostream&);

    // This hook method is a placeholder for prompting the user for
    // input.
    virtual void promptUser() = 0;

    // This hook method gets user input.
    virtual bool getInput(std::string&);

    // This hook method is a placeholder for making a command based on
    // the user input.
    virtual Command makeCommand(const std::string&) = 0;

    // This hook method executes a command.
    virtual bool executeCommand(Command command);

    // The context where the expression tree state resides.
    Context context;
    // A factory for creating a command.
    CommandFactory* commandFactory;
    // Handle to last valid command that was executed.
    Command lastValidCommand;
};

/**
 * @class VerboseHandler
 * @brief Provides a concrete interface for verbosely handling input
 *        events associated with the expression tree application.
 *
 *        This class plays the role of "concrete event handler" in the Reactor
 *        pattern and overrides several hook methods for use in the
 *        Template Method pattern.
 */
class VerboseHandler : public EventHandler {
public:
    explicit VerboseHandler(std::ostream&);

protected:
    // This hook method verbosely prompts the user for input.
    void promptUser() override;
    // This hook method makes the appropriate command based on the user input.
    Command makeCommand(const std::string&) override;
};

/**
 * @class MacroHandler
 * @brief Provides a concrete interface for less verbosely handling input
 *        events associated with the expression tree application.
 *
 *        This class plays the role of "concrete event handler" in the Reactor
 *        pattern and overrides several hook methods for use in the
 *        Template Method pattern.
 */
class MacroHandler : public EventHandler {
public:
    explicit MacroHandler(std::ostream&);

protected:
    // This hook method less verbosely prompts the user for input.
    void promptUser() override;
    // This hook method makes the appropriate set of macro commands based on the user input.
    Command makeCommand(const std::string&) override;
};

#endif // EVENT_HANDLER_H
