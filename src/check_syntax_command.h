#ifndef CHECK_SYNTAX_COMMAND_H
#define CHECK_SYNTAX_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

class check_syntax_command : public without_result_command
{
public:
    check_syntax_command(const std::string& request);

    std::string execute(const command_context& context) override;

private:
    void handle_insert(const std::vector<std::string>& tokens,
                       const command_context& context);
    void handle_truncate(const std::vector<std::string>& tokens,
                         const command_context& context);
    void handle_intersection(const std::vector<std::string> &tokens,
                             const command_context& context);
    void handle_symmetric_difference(const std::vector<std::string> &tokens,
                                     const command_context& context);
private:
    std::string _request;
};

#endif // CHECK_SYNTAX_COMMAND_H
