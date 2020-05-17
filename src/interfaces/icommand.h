#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "../session.h"
#include "icore.h"

#include <string>
#include <memory>

enum class command_type : uint8_t
{
    command_with_result,
    command_without_result
};

struct command_context
{
    std::shared_ptr<session> sess;
    std::shared_ptr<icore> core;
};

class icommand
{
public:
    virtual ~icommand() = default;
    virtual std::string execute(const command_context&) = 0;
    virtual command_type get_command_type() const = 0;
};

class without_result_command : public icommand
{
public:
    command_type get_command_type() const {
        return command_type::command_without_result;
    }
};


class with_result_command : public icommand
{
public:
    command_type get_command_type() const {
        return command_type::command_with_result;
    }
};

#endif // ICOMMAND_H
