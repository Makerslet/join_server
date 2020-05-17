#include "session.h"
#include "check_syntax_command.h"
#include "interfaces/execution_unit.h"

#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>

#include <iostream>

session::session(bio::ip::tcp::socket socket,
                 std::shared_ptr<icore> core) :
    _socket(std::move(socket)),
    _core(core),
    _read_buffer(1500),
    _input_stream(&_read_buffer),
    _output_stream(&_write_buffer),
    _is_sending(false)
{}

void session::start()
{
    if(!_read_callback)
        _read_callback = create_read_lambda();

    read();
}

void session::send(const std::string& response)
{
    if(!_write_callback)
        _write_callback = create_write_lambda();

    auto write_adder = [response, this]()
    {
        _output_stream << response;

        if(!_is_sending)
        {
            _is_sending = true;
            bio::async_write(_socket, _write_buffer, _write_callback);
        }
    };

    bio::post(_socket.get_executor(), write_adder);
}

void session::read()
{
    bio::async_read_until(_socket, _read_buffer, '\n', _read_callback);
}

void session::finish_handling()
{}

void session::clear_buffer()
{
    _read_buffer.commit(_read_buffer.max_size());
    _read_buffer.consume(_read_buffer.max_size());
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

            auto command = std::make_unique<check_syntax_command>(std::move(line));
            command_context context {shared_from_this(), _core};
            _core->add_command(std::make_unique<execution_unit>(std::move(command), context));

            read();
        }
    };
}

session::write_cb_signature session::create_write_lambda()
{
    auto self(shared_from_this());
    return [this, self](boost::system::error_code ec, std::size_t length)
    {
        _write_buffer.consume(length);

        if(!ec.failed())
        {
            if(_write_buffer.size() != 0)
                bio::async_write(_socket, _write_buffer, _write_callback);
            else
                _is_sending = false;
        }
    };
}
