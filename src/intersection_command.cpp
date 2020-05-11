#include "intersection_command.h"

intersection_command::intersection_command(std::shared_ptr<icore> core,
                                   std::shared_ptr<session> session) :
    _core(core),
    _session(session)
{}

void intersection_command::execute()
{

}
