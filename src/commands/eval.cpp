/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "commands/eval.h"
#include "core/context.h"

EvalCommand::EvalCommand(Context& context, std::string evalFormat)
    : Command_Impl(context)
    , format(std::move(evalFormat))
{
}

bool EvalCommand::execute()
{
    context.output() << context.evaluate(format) << std::endl;
    return true;
}
