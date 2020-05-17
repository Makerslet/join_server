#ifndef ITABLES_MANAGER_H
#define ITABLES_MANAGER_H

#include "../table.h"

#include <string>

class itables_manager
{
public:
    virtual ~itables_manager() = default;
    virtual bool contain_table(const std::string& name) = 0;
    virtual std::shared_ptr<table> add_table(const std::string& name) = 0;
    virtual std::shared_ptr<table> get_table(const std::string& table_name) = 0;
    virtual void remove_table(const std::string& table_name) = 0;
};

#endif // ITABLES_MANAGER_H
