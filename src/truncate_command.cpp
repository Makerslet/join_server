#include "truncate_command.h"

truncate_command::truncate_command(const std::string& table_name,
                                   std::shared_ptr<icore> core,
                                   std::shared_ptr<session> session) :
    _table_name(table_name),
    _core(core),
    _session(session)
{}

void truncate_command::execute()
{

}
