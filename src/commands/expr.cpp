/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "commands/expr.h"
#include "core/context.h"

ExprCommand::ExprCommand(Context& context, std::string newExpr)
    : Command_Impl(context)
    , expression(std::move(newExpr))
{
}

bool ExprCommand::execute()
{
    context.makeTree(expression);
    return true;
}
