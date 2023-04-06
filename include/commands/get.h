//
// Created by noaho on 11/29/2022.
//

#ifndef GET_H
#define GET_H

#include "commands/command_impl.h"
#include <string>

/**
 * @class GetCommand
 * @brief Returns the value of the variable parameter
 */
class GetCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context.
    explicit GetCommand(Context&, std::string);

    // Return the variable value
    bool execute() override;

private:
    // Format to use for the evaluation.
    std::string pair;
};

#endif // GET_H
