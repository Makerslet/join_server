#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

class insert_command : public icommand
{
public:
    insert_command(const std::string& table_name,
                   const std::vector<std::string>& values,
                   std::shared_ptr<icore> core,
                   std::shared_ptr<session> session);

    void execute() override;

private:
    std::string _table_name;
    std::vector<std::string> _values;
    std::shared_ptr<icore> _core;
    std::shared_ptr<session> _session;
};

#endif // INSERT_COMMAND_H
