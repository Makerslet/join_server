#ifndef TABLE_H
#define TABLE_H

#include <boost/thread/shared_mutex.hpp>

#include <map>
#include <functional>

class table
{
public:
    using intersection_row = std::tuple<std::size_t, std::string, std::string>;
    using sym_diff_row = std::tuple<std::size_t, std::string, std::string>;

public:
    table();
    table(table &arg);

    bool line_exists(std::size_t id);
    bool insert(std::size_t id, const std::string& name);

    std::vector<intersection_row> intersection(const table& table);
    std::vector<sym_diff_row> sym_diff(const table& table);

private:
    std::map<std::size_t, std::string> get_content();

private:
    boost::shared_mutex _rw_mutex;
    std::map<std::size_t, std::string> _table_content;
};

#endif // TABLE_H
