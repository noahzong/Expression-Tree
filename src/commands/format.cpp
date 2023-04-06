/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "commands/format.h"
#include "core/context.h"

FormatCommand::FormatCommand(Context& context, std::string newFormat)
    : Command_Impl(context)
    , format(std::move(newFormat))
{
}

bool FormatCommand::execute()
{
    context.format(format);
    return true;
}
