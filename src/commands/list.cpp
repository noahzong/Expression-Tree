//
// Created by noaho on 11/29/2022.
//

#include "commands/list.h"
#include "core/context.h"

ListCommand::ListCommand(Context& context, std::string params)
    : Command_Impl(context)
{
    (void)params;
}

bool ListCommand::execute()
{
    context.list();
    return true;
}
