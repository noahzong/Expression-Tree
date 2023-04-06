//
// Created by noaho on 11/30/2022.
//

#ifndef HISTORY_H
#define HISTORY_H

#include "commands/command_impl.h"
#include <string>

/**
 * @class HistoryCommand
 * @brief Prints out the last five valid commands
 */
class HistoryCommand : public Command_Impl {
public:
    // Constructor that provides the appropriate Context.
    explicit HistoryCommand(Context&, std::string);

    // Return the variable value
    bool execute() override;
};

#endif // HISTORY_H
