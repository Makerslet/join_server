#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "interfaces/icommand_handler.h"

class command_handler : public icommand_handler
{
public:
    command_handler();
    void push_command(std::unique_ptr<icommand>&&) override;
    void start_handling() override;
};

#endif // COMMAND_HANDLER_H
