#ifndef ICOMMAND_HANDLER_H
#define ICOMMAND_HANDLER_H

#include "icommand.h"

#include <memory>

class icommand_handler
{
public:
    virtual ~icommand_handler() = default;
    virtual void push_command(std::unique_ptr<icommand>&&) = 0;
    virtual void start_handling() = 0;
};

#endif // ICOMMAND_HANDLER_H