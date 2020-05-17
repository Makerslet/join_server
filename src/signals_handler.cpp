#include "signals_handler.h"

signals_handler::sig_handler_signature signals_handler::create_sigs_handler(
        std::shared_ptr<icore> core,
        std::shared_ptr<iserver> server)
{
    return [core, server](const boost::system::error_code&, int)
    {
        server->stop();
        core->stop();

        std::exit(0);
    };
}

