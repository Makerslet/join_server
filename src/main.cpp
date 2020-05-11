#include "args_parser.h"
#include "async_server.h"

#include <boost/asio/io_context.hpp>

namespace bio = boost::asio;

/**
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 * @return Program exit status
 */

int main (int argc, char** argv)
{
    args_parser parser;
    auto result = parser.parse(argc, argv);
    if(!result.has_value())
        return 0;

    bio::io_context io_context;
    async_server server(io_context, result.value(), std::shared_ptr<icore>());
    server.start();
    io_context.run();

    return 0;
}


