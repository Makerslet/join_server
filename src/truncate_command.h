#ifndef TRUNCATE_COMMAND_H
#define TRUNCATE_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

class truncate_command : public icommand
{
public:
    truncate_command(const std::string& table_name,
                     std::shared_ptr<icore> core,
                     std::shared_ptr<session> session);
    void execute() override;

private:
    std::string _table_name;
    std::shared_ptr<icore> _core;
    std::shared_ptr<session> _session;
};

#endif // TRUNCATE_COMMAND_H
