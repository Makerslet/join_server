#include "symmetric_difference_command.h"
#include "command_handling_exception.h"

#include <sstream>

symmetric_difference_command::symmetric_difference_command(const std::string& table1_name,
        const std::string& table2_name) :
    _table1_name(table1_name),
    _table2_name(table2_name)
{}

std::optional<std::string> symmetric_difference_command::execute(const command_context& context)
{
    auto tables_manager = context.core->tables_manager();

    auto table1_sptr = tables_manager->get_table(_table1_name);
    if(!table1_sptr)
    {
        std::string error("SYMMETRIC DIFFERENCE command: server doesnt't contain table " + _table1_name);
        throw command_handling_exception(error);
    }

    auto table2_sptr = tables_manager->get_table(_table2_name);
    if(!table2_sptr)
    {
        std::string error("SYMMETRIC DIFFERENCE command: server doesnt't contain table " + _table2_name);
        throw command_handling_exception(error);
    }

    table table_left_copy(*table1_sptr);
    table table_right_copy(*table2_sptr);

    std::vector<table::sym_diff_row> result = table_left_copy.sym_diff(table_right_copy);
    return to_string(result);
}

std::string symmetric_difference_command::to_string(const std::vector<table::sym_diff_row>& rows)
{
    std::stringstream ss;

    for(const auto& row : rows)
    {
        std::string leftPart = std::get<1>(row).empty() ? "---" : std::get<1>(row);
        std::string rightPart = std::get<2>(row).empty() ? "---" : std::get<2>(row);

        ss << std::get<0>(row) << " " << leftPart << " " << rightPart << "\n";
    }

    return ss.str();
}
