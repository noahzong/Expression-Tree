//
// Created by noaho on 11/29/2022.
//

#include "commands/get.h"
#include "core/context.h"

GetCommand::GetCommand(Context& context, std::string pair)
    : Command_Impl(context)
    , pair(std::move(pair))
{
}

bool GetCommand::execute()
{
    context.get(pair);
    return true;
}
