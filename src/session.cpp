#include "session.h"

session::session(bio::ip::tcp::socket socket,
                 std::shared_ptr<icore> core) :
    _socket(std::move(socket)),
    _core(core)
{}

void session::start()
{
    if(!_read_callback)
        _read_callback = create_read_lambda();

    read();
}

void session::read()
{
    auto self(shared_from_this());
    _socket.async_read_some(boost::asio::buffer(_buffer), _read_callback);
}

void session::handle_request(std::string)
{
}

void session::finish_handling()
{}

session::read_cb_signature session::create_read_lambda()
{
    auto self(shared_from_this());
    return [this, self](boost::system::error_code ec, std::size_t length)
    {
        if(ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset)
            finish_handling();
        else
        {
            handle_request(std::string(_buffer.data(), length));
            read();
        }
    };
}
