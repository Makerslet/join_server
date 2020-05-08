#include "async_server.h"
#include "session.h"

async_server::async_server(bio::io_context& io_context, unsigned short port,
               std::shared_ptr<icore> core) :
    _acceptor(io_context, bio::ip::tcp::endpoint(bio::ip::tcp::v4(), port)),
    _core(core)
{
}

void async_server::start()
{
    if(!_accept_functor)
        _accept_functor = create_accept_lambda();

    accept();
}

void async_server::accept()
{
    _acceptor.async_accept(create_accept_lambda());
}

void async_server::stop()
{
    _acceptor.close();
}

async_server::accept_cb_signature async_server::create_accept_lambda()
{
    return [this](boost::system::error_code ec, bio::ip::tcp::socket socket)
    {
        if (ec == boost::system::errc::success)
            std::make_shared<session>(std::move(socket), _core)->start();

        accept();
    };
}
