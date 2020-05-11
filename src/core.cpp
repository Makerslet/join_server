#include "core.h"

core::core(std::shared_ptr<itables_manager> tables_manager,
           std::shared_ptr<icommand_handler> command_handler):
    _tables_manager(tables_manager),
    _command_handler(command_handler)
{}

std::shared_ptr<itables_manager> core::tables_manager()
{
    return _tables_manager;
}

void core::add_command(std::unique_ptr<icommand>&& command)
{
    _command_handler->push_command(std::move(command));
}
