#include "insert_command.h"
#include "command_handling_exception.h"

insert_command::insert_command(const std::string& table_name,
               const std::vector<std::string>& values) :
    _table_name(table_name),
    _values(values)
{}

std::string insert_command::execute(const command_context& context)
{
    auto tables_manager = context.core->tables_manager();
    table_sptr t_sptr;
    if(!tables_manager->contain_table(_table_name))
        t_sptr = tables_manager->add_table(_table_name);
    else
        t_sptr = tables_manager->get_table(_table_name);

    // throw if can't cast
    std::size_t id = extract_id();
    std::string name = _values[1];

    if(!t_sptr->insert(id, name))
    {
        std::string error("INSERT command: line with id " + std::to_string(id) + " already exists");
        throw command_handling_exception(error);
    }

    return std::string();
}

std::size_t insert_command::extract_id()
{
    try {
        return std::stoull(_values[0]);
    }
    catch(const std::invalid_argument&) {
        throw command_handling_exception("INSERT command: wrong id type");
    }
    catch(const std::out_of_range&) {
        throw command_handling_exception("INSERT command: id out of range");
    }
}

