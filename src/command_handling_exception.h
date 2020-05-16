#ifndef COMMAND_HANDLING_EXCEPTION_H
#define COMMAND_HANDLING_EXCEPTION_H

#include <stdexcept>

class command_handling_exception : public std::runtime_error
{
public:
    command_handling_exception(const std::string& error);
};

#endif // COMMAND_HANDLING_EXCEPTION_H
