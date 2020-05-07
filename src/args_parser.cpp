#include "args_parser.h"

#include <iostream>

args_parser::args_parser() :
    _description("allowed options")
{
    _description.add_options()
            ("help", "input arguments description")
            ("port", boost::program_options::value<short>(),
             "set server listen port (required)");
}

std::optional<unsigned short> args_parser::parse(int argc, char **argv)
{
    std::optional<unsigned short> result;
    try {
        auto parsed_options = boost::program_options::parse_command_line(argc, argv, _description);
        boost::program_options::store(parsed_options, _values_storage);

        if(_values_storage.count("help"))
        {
            std::cout << _description << std::endl;
            return result;
        }

        if(!_values_storage.count("port"))
            throw std::logic_error("server listen port wasn't set");
        else
        {
            int port = _values_storage["port"].as<short>();
            if(port < 0)
                throw std::logic_error("port can't have a negative value");
            if(port == 0)
                throw std::logic_error("port can't have 0");

            result = static_cast<unsigned short>(port);
        }
    }
    catch(const std::logic_error& ex)
    {
        std::cout << "error: " << ex.what() << std::endl;
        std::cout << _description;

        result.reset();
        return result;
    }

    return result;
}
