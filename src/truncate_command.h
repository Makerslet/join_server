#ifndef TRUNCATE_COMMAND_H
#define TRUNCATE_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

class truncate_command : public with_result_command
{
public:
    truncate_command(const std::string& table_name);
    std::string execute(const command_context& context) override;

private:
    std::string _table_name;
};

#endif // TRUNCATE_COMMAND_H
