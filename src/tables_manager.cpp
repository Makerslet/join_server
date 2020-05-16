#include "tables_manager.h"

bool tables_manager::contain_table(const std::string& name)
{
    boost::shared_lock<boost::shared_mutex> lock(_rw_lock);
    return _tables.find(name) != _tables.end();
}

std::shared_ptr<table> tables_manager::add_table(const std::string& name)
{
    boost::unique_lock<boost::shared_mutex> lock(_rw_lock);
    auto iter = _tables.find(name);
    if(iter != _tables.end())
        return iter->second;

    auto result = _tables.emplace(name, std::make_shared<table>());
    return result.first->second;
}

std::shared_ptr<table> tables_manager::get_table(const std::string& table_name)
{
    boost::shared_lock<boost::shared_mutex> lock(_rw_lock);
    table_sptr t_sptr;

    auto iter = _tables.find(table_name);
    if(iter != _tables.end())
        t_sptr = iter->second;
    return t_sptr;
}
