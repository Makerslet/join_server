#ifndef TABLE_H
#define TABLE_H

#include <boost/thread/shared_mutex.hpp>

#include <map>
#include <functional>

class table
{
    using intersection_row = std::tuple<std::size_t, std::string, std::string>;
    using sym_diff_row = std::tuple<std::size_t, std::string, std::string>;

public:
    table();

    bool line_exists(std::size_t id);
    bool insert(std::size_t id, const std::string& name);

    std::vector<intersection_row> intersection(const table& table);
    std::vector<sym_diff_row> sym_diff(const table& table);

private:
    boost::shared_mutex _rw_mutex;
    std::map<std::size_t, std::string> _table_content;
};

#endif // TABLE_H
