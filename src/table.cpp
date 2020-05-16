#include "table.h"

table::table()
{}

bool table::line_exists(std::size_t id)
{
    boost::shared_lock<boost::shared_mutex> lock(_rw_mutex);
    return _table_content.find(id) != _table_content.end();
}

bool table::insert(std::size_t id, const std::string& name)
{
    boost::unique_lock<boost::shared_mutex> lock(_rw_mutex);
    auto result = _table_content.try_emplace(id, name);
    return result.second;
}

std::vector<table::intersection_row> table::intersection(const table&)
{
    return std::vector<table::intersection_row>();
}

std::vector<table::sym_diff_row> table::sym_diff(const table&)
{
    return std::vector<table::sym_diff_row>();
}
