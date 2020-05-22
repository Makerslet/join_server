#include "table.h"
#include <set>

table::table()
{}

table::table(table& arg) :
    _table_content(arg.get_content())
{}

bool table::operator==(table& arg)
{
    boost::shared_lock<boost::shared_mutex> lock_l(_rw_mutex);
    boost::shared_lock<boost::shared_mutex> lock_r(arg._rw_mutex);
    return _table_content == arg._table_content;
}

bool table::empty()
{
    boost::shared_lock<boost::shared_mutex> lock_l(_rw_mutex);
    return _table_content.empty();
}

bool table::line_exists(std::size_t id)
{
    boost::shared_lock<boost::shared_mutex> lock(_rw_mutex);
    return _table_content.find(id) != _table_content.end();
}

std::string table::line_value(std::size_t id)
{
    boost::shared_lock<boost::shared_mutex> lock(_rw_mutex);
    auto iter = _table_content.find(id);
    return iter != _table_content.end() ? iter->second : std::string();
}

std::map<std::size_t, std::string> table::get_content()
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

std::vector<table::intersection_row> table::intersection(const table& other)
{
    std::vector<intersection_row> result;

    for(const auto& row : _table_content)
    {
        auto other_iter = other._table_content.find(row.first);

        if(other_iter != other._table_content.end())
            result.emplace_back(row.first, row.second, other_iter->second);
    }

    return result;
}

std::vector<table::sym_diff_row> table::sym_diff(const table& other)
{
    std::vector<sym_diff_row> sym_diff_result;
    std::set<std::size_t> intersect;

    for(const auto& row : _table_content)
    {
        auto other_iter = other._table_content.find(row.first);

        if(other_iter != other._table_content.end())
            intersect.insert(row.first);
        else
            sym_diff_result.emplace_back(row.first, row.second, "");
    }

    for(const auto& row : other._table_content)
    {
        auto intersect_iter = intersect.find(row.first);

        if(intersect_iter == intersect.end())
            sym_diff_result.emplace_back(row.first, "", row.second);
    }

    auto comparator = [](const sym_diff_row& left, const sym_diff_row& right)
        {return  std::get<0>(left) < std::get<0>(right);};
    std::sort(sym_diff_result.begin(), sym_diff_result.begin(), comparator);

    return sym_diff_result;
}
