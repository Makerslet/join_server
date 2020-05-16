#include "truncate_command.h"

truncate_command::truncate_command(const std::string& table_name) :
    _table_name(table_name)
{}

std::string truncate_command::execute(const command_context&)
{
    return "";
}
