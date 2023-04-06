/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "commands/quit.h"
#include "core/context.h"
#include "core/reactor.h"

QuitCommand::QuitCommand(Context& context)
    : Command_Impl(context)
{
}

bool QuitCommand::execute()
{
    context.output() << "Stopping now.  Have a great day...";
    // Set reactor run flag to false
    Reactor::instance()->endEventLoop();
    return false;
}
