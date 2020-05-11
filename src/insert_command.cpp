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

}
