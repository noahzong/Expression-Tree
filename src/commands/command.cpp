/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "commands/command.h"
#include "commands/command_impl.h"

Command::Command(Command_Impl* command)
    : bridge(command)
{
}

bool Command::execute()
{
    return bridge->execute();
}
