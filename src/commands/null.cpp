/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "commands/null.h"
#include "core/context.h"

NullCommand::NullCommand(Context& context)
    : Command_Impl(context)
{
}

bool NullCommand::execute()
{
    return true;
}
