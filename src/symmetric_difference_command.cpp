#include "symmetric_difference_command.h"
#include "command_handling_exception.h"

#include <sstream>

symmetric_difference_command::symmetric_difference_command(const std::string& table1_name,
        const std::string& table2_name) :
    _table1_name(table1_name),
    _table2_name(table2_name)
{}

std::string symmetric_difference_command::execute(const command_context& context)
{
    auto tables_manager = context.core->tables_manager();

    if(!tables_manager->contain_table(_table1_name))
    {
        std::string error("server doesnt't contain table " + _table1_name);
        throw command_handling_exception(error);
    }

    if(!tables_manager->contain_table(_table2_name))
    {
        std::string error("server doesnt't contain table " + _table2_name);
        throw command_handling_exception(error);
    }

    table table_left_copy(*tables_manager->get_table(_table1_name));
    table table_right_copy(*tables_manager->get_table(_table2_name));

    auto result = table_left_copy.intersection(table_right_copy);
    return to_string(result);
}

std::string symmetric_difference_command::to_string(const std::vector<table::intersection_row>& rows)
{
    std::string result;
    std::stringstream ss;

    for(const auto& row : rows)
    {
        ss << std::get<0>(row) << " " << std::get<1>(row) << " " << std::get<2>(row) << "\n";
        result += ss.str();
        ss.clear();
    }

    return result;
}
