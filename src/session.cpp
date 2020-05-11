#include "session.h"
#include "check_syntax_command.h"

#include <boost/asio/read_until.hpp>

#include <iostream>

session::session(bio::ip::tcp::socket socket,
                 std::shared_ptr<icore> core) :
    _socket(std::move(socket)),
    _core(core),
    _buffer(1500),
    _input_stream(&_buffer)
{}

void session::start()
{
    if(!_read_callback)
        _read_callback = create_read_lambda();

    read();
}

void session::send(const std::string&)
{

}

void session::read()
{
    auto self(shared_from_this());
    bio::async_read_until(_socket, _buffer, '\n', _read_callback);
}

void session::handle_request(std::string)
{
}

void session::finish_handling()
{}

void session::clear_buffer()
{
    _buffer.commit(_buffer.max_size());
    _buffer.consume(_buffer.max_size());
}

session::read_cb_signature session::create_read_lambda()
{
    auto self(shared_from_this());
    return [this, self](boost::system::error_code ec, std::size_t)
    {
        if(ec == boost::asio::error::eof || ec == boost::asio::error::connection_reset)
            finish_handling();
        else if(ec == boost::asio::error::not_found)
        {
            // что делать здесь не понятно, наверное стоит очистить данные из буфера
            clear_buffer();
            read();
        }
        else
        {
            std::string line;
            std::getline(_input_stream, line);

            auto command = std::make_unique<check_syntax_command>(std::move(line), _core, shared_from_this());
            _core->add_command(std::move(command));

            read();
        }
    };
}
