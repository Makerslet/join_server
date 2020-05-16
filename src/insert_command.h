#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

class insert_command : public with_result_command
{
    using table_sptr = std::shared_ptr<table>;
public:
    insert_command(const std::string& table_name,
                   const std::vector<std::string>& values);

    std::string execute(const command_context& context);

private:
    std::size_t extract_id();

private:
    std::string _table_name;
    std::vector<std::string> _values;
};

#endif // INSERT_COMMAND_H
