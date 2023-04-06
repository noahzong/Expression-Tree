/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "commands/set.h"
#include "core/context.h"

SetCommand::SetCommand(Context& context, std::string pair)
    : Command_Impl(context)
    , pair(std::move(pair))
{
}

bool SetCommand::execute()
{
    context.set(pair);
    return true;
}