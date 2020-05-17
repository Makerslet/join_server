#ifndef INTERSECTION_COMMAND_H
#define INTERSECTION_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

class intersection_command : public with_result_command
{
public:
    intersection_command(const std::string& table1_name,
                         const std::string& table2_name);

    std::string execute(const command_context& context);

private:
    std::string to_string(const std::vector<table::intersection_row>& rows);

private:
    std::string _table1_name;
    std::string _table2_name;
};

#endif // INTERSECTION_COMMAND_H
