#ifndef SYMMETRIC_DIFFERENCE_COMMAND_H
#define SYMMETRIC_DIFFERENCE_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

class symmetric_difference_command : public icommand
{
public:
    symmetric_difference_command(std::shared_ptr<icore> core,
                                 std::shared_ptr<session> session);

    void execute() override;

private:
    std::shared_ptr<icore> _core;
    std::shared_ptr<session> _session;
};

#endif // SYMMETRIC_DIFFERENCE_COMMAND_H
