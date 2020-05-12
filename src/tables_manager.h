#ifndef TABLES_MANAGER_H
#define TABLES_MANAGER_H

#include "interfaces/itables_manager.h"

#include <boost/thread/shared_mutex.hpp>

class tables_manager : public itables_manager
{
    using table_sptr = std::shared_ptr<table>;
public:
    tables_manager();
    bool contain_table(const std::string& name) override;
    std::shared_ptr<table> add_table(const std::string& name) override;
    std::shared_ptr<table> get_table(const std::string& table_name) override;

private:
    boost::shared_mutex _rw_lock;
    std::unordered_map<std::string, table_sptr> _tables;
};

#endif // TABLES_MANAGER_H
