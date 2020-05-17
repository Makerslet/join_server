#include "truncate_command.h"
#include "command_handling_exception.h"

truncate_command::truncate_command(const std::string& table_name) :
    _table_name(table_name)
{}

std::string truncate_command::execute(const command_context& context)
{
    auto tables_manager = context.core->tables_manager();

    bool contains = tables_manager->contain_table(_table_name);
    if(!contains)
    {
        std::string error("TRUNCATE command: server doesnt't contain table " + _table_name);
        throw command_handling_exception(error);
    }

    tables_manager->remove_table(_table_name);
    return "OK";
}
