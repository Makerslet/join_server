#ifndef CHECK_SYNTAX_COMMAND_H
#define CHECK_SYNTAX_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

class check_syntax_command : public icommand
{
    class wrong_syntax_command : public std::invalid_argument
    {
    public:
        wrong_syntax_command(const std::string& err) :
            std::invalid_argument(err)
        {}
    };

public:
    check_syntax_command(const std::string& request,
                         std::shared_ptr<icore> core,
                         std::shared_ptr<session> session);

    void execute() override;

private:
    void handle_insert(const std::vector<std::string>& tokens);
    void handle_truncate(const std::vector<std::string>& tokens);
    void handle_intersection(const std::vector<std::string> &tokens);
    void handle_symmetric_difference(const std::vector<std::string> &tokens);

    void response_error(const std::string& description);

private:
    std::string _request;
    std::shared_ptr<icore> _core;
    std::shared_ptr<session> _session;

};

#endif // CHECK_SYNTAX_COMMAND_H
