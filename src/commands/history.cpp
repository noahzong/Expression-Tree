//
// Created by noaho on 11/30/2022.
//

#include "commands/history.h"
#include "core/context.h"

HistoryCommand::HistoryCommand(Context& context, std::string params)
    : Command_Impl(context)
{
    (void)params;
}

bool HistoryCommand::execute()
{
    context.history();
    return true;
}