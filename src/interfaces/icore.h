#ifndef ICORE_H
#define ICORE_H

#include "itables_manager.h"
#include "iserver.h"

#include <memory>

class execution_unit;

class icore
{
public:
    virtual ~icore() = default;
    virtual std::shared_ptr<itables_manager> tables_manager() = 0;
    virtual void add_command(std::unique_ptr<execution_unit>&&) = 0;

    virtual void start() = 0;
    virtual void stop() = 0;
};

#endif // ICORE_H
