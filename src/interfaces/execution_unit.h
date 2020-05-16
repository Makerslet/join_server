#ifndef EXECUTION_UNIT_H
#define EXECUTION_UNIT_H

#include "icommand.h"
#include <memory>

struct execution_unit
{
    execution_unit(std::unique_ptr<icommand>&& cmd, command_context context) :
        command(std::move(cmd)), context(context)
    {}

    std::unique_ptr<icommand> command;
    command_context context;
};

#endif // EXECUTION_UNIT_H
