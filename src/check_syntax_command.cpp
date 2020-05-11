#include "check_syntax_command.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

check_syntax_command::check_syntax_command(const std::string& request,
                     std::shared_ptr<icore> core,
                     std::shared_ptr<session> session) :
    _request(request), _core(core), _session(session)
{}

void check_syntax_command::execute()
{
    try{
        if(_request.empty())
            throw wrong_syntax_command("empty request");

        std::vector<std::string> tokens;
        boost::algorithm::split(tokens, _request, boost::is_space());

        if(tokens[0] == "INSERT")
            handle_insert(tokens);
        else if(tokens[0] == "TRUNCATE")
            handle_truncate(tokens);
        else if(tokens[0] == "INTERSECTION")
            handle_intersection(tokens);
        else if(tokens[0] == "SYMMETRIC_DIFFERENCE")
            handle_symmetric_difference(tokens);
        else
            throw wrong_syntax_command("empty request");
    }
    catch(const wrong_syntax_command& ex) {
        response_error(std::string("ERR ") + ex.what());
    }

}

void check_syntax_command::handle_insert(const std::vector<std::string>& tokens)
{
    if(tokens.size() == 4)
    {
        //create insert_command
    }
    else
    {
        std::string error("INSERT command contains wrong number of arguments (need 3, contains " +
                          std::to_string(tokens.size() - 1) + ")");
        throw wrong_syntax_command(error);
    }
}

void check_syntax_command::handle_truncate(const std::vector<std::string>& tokens)
{
    if(tokens.size() == 2)
    {
        //create truncate
    }
    else
    {
        std::string error("TRUNCATE command contains wrong number of arguments (need 1, contains " +
                          std::to_string(tokens.size() - 1) + ")");
        throw wrong_syntax_command(error);
    }
}

void check_syntax_command::handle_intersection(const std::vector<std::string>& tokens)
{
    if(tokens.size() == 1)
    {
        //create intersection
    }
    else
    {
        std::string error("INTERSECTION command can't contain arguments, but contains " +
                          std::to_string(tokens.size() - 1));
        throw wrong_syntax_command(error);
    }
}

void check_syntax_command::handle_symmetric_difference(const std::vector<std::string>& tokens)
{
    if(tokens.size() == 1)
    {
        //create symmetric difference
    }
    else
    {
        std::string error("SYMMETRIC_DIFFERENCE command can't contain arguments, but contains " +
                          std::to_string(tokens.size() - 1));
        throw wrong_syntax_command(error);
    }
}


void check_syntax_command::response_error(const std::string& description)
{
    _session->send(description);
}
