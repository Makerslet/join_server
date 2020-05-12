#include "table.h"

table::table()
{}

bool table::line_exists(std::size_t id)
{
    boost::shared_lock<boost::shared_mutex> lock(_rw_mutex);
    return _table_content.find(id) != _table_content.end();
}

std::map<std::size_t, std::string> table::table_content()
{
    boost::shared_lock<boost::shared_mutex> lock(_rw_mutex);
    return _table_content;
}

bool table::insert(std::size_t id, const std::string& name)
{
    boost::unique_lock<boost::shared_mutex> lock(_rw_mutex);
    auto result = _table_content.try_emplace(id, name);
    return result.second;
}
