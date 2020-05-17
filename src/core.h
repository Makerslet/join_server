#ifndef CORE_H
#define CORE_H

#include "interfaces/icore.h"
#include "interfaces/icommand_handler.h"
#include "interfaces/execution_unit.h"

class core : public icore
{
public:
    core(std::shared_ptr<itables_manager> tables_manager,
         std::shared_ptr<icommand_handler> command_handler);
    std::shared_ptr<itables_manager> tables_manager() override;
    void add_command(std::unique_ptr<execution_unit>&&) override;
    void start() override;
    void stop() override;

private:
    std::shared_ptr<itables_manager> _tables_manager;
    std::shared_ptr<icommand_handler> _command_handler;
};

#endif // CORE_H
