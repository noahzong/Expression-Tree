/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "commands/print.h"
#include "core/context.h"
#include <sstream>

PrintCommand::PrintCommand(Context& context, std::string format)
    : Command_Impl(context)
    , format(std::move(format))
{
}

bool PrintCommand::execute()
{
    context.print(format);
    context.output() << std::endl;
    return true;
}
