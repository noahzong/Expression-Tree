/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "commands/macro.h"
#include "core/context.h"
#include <algorithm>
#include <functional>

MacroCommand::MacroCommand(Context& context, std::vector<Command> macroCommands)
    : Command_Impl(context)
    , commands(std::move(macroCommands))
{
}

bool MacroCommand::execute()
{
    std::for_each(commands.begin(), commands.end(), std::mem_fn(&Command::execute));
    return true;
}