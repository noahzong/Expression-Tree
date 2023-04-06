/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include <string>
#include <unordered_map>

// Forward declarations.
class Context;
class Command;

/**
 * @class CommandFactory
 * @brief This is a factory to create expression tree commands.
 */
class CommandFactory {
public:
    // Default constructor
    CommandFactory(Context& ctx);

    // Dtor
    virtual ~CommandFactory() = default;

    // Make the requested command.  This method is the primary method used by clients.
    virtual Command makeCommand(const std::string&);

    // Make the requested format command.
    virtual Command makeFormatCommand(const std::string&);

    // Make the requested expression command.
    virtual Command makeExprCommand(const std::string&);

    // Make the requested print command.
    virtual Command makePrintCommand(const std::string&);

    // Make the requested eval command.
    virtual Command makeEvalCommand(const std::string&);

    // Make the requested eval command.
    virtual Command makeSetCommand(const std::string&);

    // Make the requested quit command.
    virtual Command makeQuitCommand(const std::string& params);

    // Make the requested macro command.
    virtual Command makeMacroCommand(const std::string&);

    // Make the requested null command.
    virtual Command makeNullCommand(const std::string& params);

    // Make the requested get command.
    virtual Command makeGetCommand(const std::string& params);

    // Make the requested list command.
    virtual Command makeListCommand(const std::string& params);

    // Make the requested list command.
    virtual Command makeHistoryCommand(const std::string& params);

private:
    // Useful typedefs to simplify use of the STL @std::map.
    typedef Command (CommandFactory::*FACTORY_PTMF)(const std::string&);
    typedef std::unordered_map<std::string, FACTORY_PTMF> COMMAND_MAP;
    // Map used to validate user command input and dispatch corresponding factory method.
    COMMAND_MAP commandMap;
    // Holds the expression tree that is the target of the commands.
    Context& context;
};

#endif // COMMAND_FACTORY_H
