#ifndef INTERSECTION_COMMAND_H
#define INTERSECTION_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

class intersection_command : public icommand
{
public:
    intersection_command(std::shared_ptr<icore> core,
                         std::shared_ptr<session> session);

    void execute() override;

private:
    std::shared_ptr<icore> _core;
    std::shared_ptr<session> _session;
};

#endif // INTERSECTION_COMMAND_H
