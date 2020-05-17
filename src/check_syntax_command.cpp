#include "check_syntax_command.h"
#include "insert_command.h"
#include "truncate_command.h"
#include "intersection_command.h"
#include "symmetric_difference_command.h"
#include "command_handling_exception.h"
#include "interfaces/execution_unit.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

check_syntax_command::check_syntax_command(const std::string& request) :
    _request(request)
{}

std::string check_syntax_command::execute(const command_context& context)
{
    if(_request.empty())
        throw command_handling_exception("empty request");

    std::vector<std::string> tokens;
    boost::algorithm::split(tokens, _request, boost::is_space());
    erase_empty_tokens(tokens);

    if(tokens[0] == "INSERT")
        handle_insert(tokens, context);
    else if(tokens[0] == "TRUNCATE")
        handle_truncate(tokens, context);
    else if(tokens[0] == "INTERSECTION")
        handle_intersection(tokens, context);
    else if(tokens[0] == "SYMMETRIC_DIFFERENCE")
        handle_symmetric_difference(tokens, context);
    else
        throw command_handling_exception("unknown command type " + tokens[0]);

    return std::string();
}

void check_syntax_command::erase_empty_tokens(std::vector<std::string>& tokens)
{
    auto predicate = [](const std::string& token) {return token.empty();};
    auto iter = std::remove_if(tokens.begin(), tokens.end(), predicate);
    tokens.erase(iter, tokens.end());
}

void check_syntax_command::handle_insert(const std::vector<std::string>& tokens,
                                         const command_context& context)
{
    // пока заложимся на фиксированный формат таблицы
    if(tokens.size() == 4)
    {
        std::string table_name(tokens[1]);
        std::vector<std::string> values(tokens.begin() + 2, tokens.end());
        auto command = std::make_unique<insert_command>(
                    std::move(table_name), std::move(values));
        context.core->add_command(std::make_unique<execution_unit>(std::move(command), context));
    }
    else
    {
        std::string error("INSERT command needs 3 arguments, but contains " +
                          std::to_string(tokens.size() - 1));
        throw command_handling_exception(error);
    }
}

void check_syntax_command::handle_truncate(const std::vector<std::string>& tokens,
                                           const command_context& context)
{
    if(tokens.size() == 2)
    {
        std::string table_name(tokens[1]);
        auto command = std::make_unique<truncate_command>(std::move(table_name));
        context.core->add_command(std::make_unique<execution_unit>(std::move(command), context));
    }
    else
    {
        std::string error("TRUNCATE command contains wrong number of arguments (need 1, contains " +
                          std::to_string(tokens.size() - 1) + ")");
        throw command_handling_exception(error);
    }
}

void check_syntax_command::handle_intersection(const std::vector<std::string>& tokens,
                                               const command_context& context)
{
    if(tokens.size() == 3)
    {
        auto command = std::make_unique<intersection_command>(tokens[1], tokens[2]);
        context.core->add_command(std::make_unique<execution_unit>(std::move(command), context));
    }
    else
    {
        std::string error("INTERSECTION command needs 2 arguments, but contains " +
                          std::to_string(tokens.size() - 1));
        throw command_handling_exception(error);
    }
}

void check_syntax_command::handle_symmetric_difference(const std::vector<std::string>& tokens,
                                                       const command_context& context)
{
    if(tokens.size() == 3)
    {
        auto command = std::make_unique<symmetric_difference_command>(tokens[1], tokens[2]);
        context.core->add_command(std::make_unique<execution_unit>(std::move(command), context));
    }
    else
    {
        std::string error("SYMMETRIC_DIFFERENCE command needs 2 arguments, but contains " +
                          std::to_string(tokens.size() - 1));
        throw command_handling_exception(error);
    }
}
