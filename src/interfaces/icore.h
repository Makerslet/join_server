#ifndef ICORE_H
#define ICORE_H

#include "icommand.h"
#include "itables_manager.h"
#include "iserver.h"

#include <memory>

class icore
{
public:
    virtual ~icore() = default;
    virtual std::shared_ptr<itables_manager> tables_manager() = 0;
    virtual std::shared_ptr<iserver> server() = 0;

    virtual void add_command(std::unique_ptr<icommand>&&) = 0;
};

#endif // ICORE_H
