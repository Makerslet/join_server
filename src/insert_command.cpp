#include "insert_command.h"

insert_command::insert_command(const std::string& table_name,
               const std::vector<std::string>& values,
               std::shared_ptr<icore> core,
               std::shared_ptr<session> session) :
    _table_name(table_name),
    _values(values),
    _core(core),
    _session(session)
{}

void insert_command::execute()
{
    try {
        auto tables_manager = _core->tables_manager();
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
            std::string error("line with id " + std::to_string(id) + " already exists");
            throw insert_command_exception(error);
        }

        _session->send("OK");
    }
    catch(const insert_command_exception& ex) {
        _session->send(std::string("ERR ") + ex.what());
    }
}

std::size_t insert_command::extract_id()
{
    try {
        return std::stoull(_values[0]);
    }
    catch(const std::invalid_argument&) {
        throw insert_command_exception("wrong id type");
    }
    catch(const std::out_of_range&) {
        throw insert_command_exception("id out of range");
    }
}

