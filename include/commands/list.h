//
// Created by noaho on 11/29/2022.
//

#ifndef LIST_H
#define LIST_H

#include "commands/command_impl.h"
#include <string>

/**
 * @class ListCommand
 * @brief Returns a list of all variables in use
 */
class ListCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context.
    explicit ListCommand(Context&, std::string);

    // Return the variable value
    bool execute() override;
};

#endif // LIST_H
