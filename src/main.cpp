#include "args_parser.h"
#include "command_handler.h"
#include "tables_manager.h"
#include "core.h"
#include "async_server.h"
#include "signals_handler.h"

#include <iostream>

#include <boost/asio/io_context.hpp>
#include <boost/asio/signal_set.hpp>

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

    auto cmd_handler = std::make_shared<command_handler>(2);
    auto tables_mngr = std::make_shared<tables_manager>();
    auto app_core = std::make_shared<core>(tables_mngr, cmd_handler);
    app_core->start();

    bio::io_context io_context;
    auto server = std::make_shared<async_server>(io_context, result.value(), app_core);
    server->start();

    boost::asio::signal_set sigs(io_context, SIGINT);
    sigs.async_wait(signals_handler::create_sigs_handler(app_core, server));

    io_context.run();

    return 0;
}


