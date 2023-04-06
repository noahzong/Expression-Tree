/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "core/event_handler.h"
#include "commands/command.h"
#include "commands/command_factory.h"
#include <iostream>

EventHandler* EventHandler::makeHandler(bool verbose, std::ostream& os)
{
    return verbose ? static_cast<EventHandler*>(new VerboseHandler(os))
                   : static_cast<EventHandler*>(new MacroHandler(os));
}

EventHandler::EventHandler(std::ostream& os)
    : context(os)
    , commandFactory(new CommandFactory(context))
    , lastValidCommand(commandFactory->makeNullCommand(""))
{
}

void EventHandler::handle()
{
    // Step 1) Prompt User
    promptUser();
    std::string input;
    // Step 2) Get user input (error getting it shuts down application immediately)
    if (!getInput(input))
        Reactor::instance()->endEventLoop();

    try {
        // Step 3) Make a command
        Command command
            = input.empty() ? commandFactory->makeQuitCommand(input) : makeCommand(input);
        // Step 4) Execute command
        executeCommand(command);
        lastValidCommand = command;
    } catch (ExpressionTree::InvalidIterator& e) {
        std::cerr << "\nERROR: Bad traversal type (" << e.what() << ")\n";
    } catch (State::InvalidState& e) {
        std::cerr << "\nERROR: " << e.what() << std::endl;
    } catch (std::logic_error& e) {
        std::cerr << e.what() << std::endl;
    } catch (std::invalid_argument e) {
        std::cerr << "\nERROR: Invalid parameter (" << e.what() << ")\n";
    }
}

bool EventHandler::getInput(std::string& input)
{
    std::getline(std::cin, input);
    return !std::cin.fail();
}

bool EventHandler::executeCommand(Command command)
{
    return command.execute();
}

VerboseHandler::VerboseHandler(std::ostream& os)
    : EventHandler(os)
{
}

void VerboseHandler::promptUser()
{
    context.state()->printValidCommands();
    context.output() << "> ";
    context.output().flush();
}

Command VerboseHandler::makeCommand(const std::string& input)
{
    return commandFactory->makeCommand(input);
}

MacroHandler::MacroHandler(std::ostream& os)
    : EventHandler(os)
{
}

void MacroHandler::promptUser()
{
    context.output() << "> ";
    context.output().flush();
}

Command MacroHandler::makeCommand(const std::string& input)
{
    return commandFactory->makeMacroCommand(input);
}
