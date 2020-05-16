#include "symmetric_difference_command.h"

symmetric_difference_command::symmetric_difference_command(const std::string& table1_name,
        const std::string& table2_name) :
    _table1_name(table1_name),
    _table2_name(table2_name)
{}

std::string symmetric_difference_command::execute(const command_context&)
{
    return "";
}
