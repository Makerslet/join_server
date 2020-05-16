#include "command_handling_exception.h"

command_handling_exception::command_handling_exception(const std::string &error) :
    std::runtime_error(error)
{}
