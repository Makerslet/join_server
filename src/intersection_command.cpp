#include "intersection_command.h"
#include "command_handling_exception.h"

intersection_command::intersection_command(const std::string& table1_name,
        const std::string& table2_name) :
    _table1_name(table1_name),
    _table2_name(table2_name)
{}

std::string intersection_command::execute(const command_context& context)
{
    auto tables_manager = context.core->tables_manager();

    auto table1_sptr = tables_manager->get_table(_table1_name);
    if(!table1_sptr)
    {
        std::string error("INTERSECION command: server doesnt't contain table " + _table1_name);
        throw command_handling_exception(error);
    }

    auto table2_sptr = tables_manager->get_table(_table2_name);
    if(table2_sptr)
    {
        std::string error("INTERSECION command: server doesnt't contain table " + _table2_name);
        throw command_handling_exception(error);
    }

    table table_left_copy(*table1_sptr);
    table table_right_copy(*table2_sptr);

    std::vector<table::intersection_row> result = table_left_copy.intersection(table_right_copy);
    return to_string(result);
}

std::string intersection_command::to_string(const std::vector<table::intersection_row>& rows)
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
