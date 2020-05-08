#ifndef ASYNC_SERVER_H
#define ASYNC_SERVER_H

#include "interfaces/iserver.h"
#include "interfaces/icore.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>

#include <array>
#include <memory>

namespace bio = boost::asio;

/**
 * @brief Класс асинхронного сервера
 */

class async_server : public iserver
{
    using accept_cb_signature = std::function<void(boost::system::error_code, bio::ip::tcp::socket)>;
public:
    async_server(bio::io_context& io_context, unsigned short port,
           std::shared_ptr<icore> core);

    void start() override;
    void stop() override;

private:
    void accept();

    // callback lambdas
private:
    accept_cb_signature create_accept_lambda();

private:
    bio::ip::tcp::acceptor _acceptor;
    std::shared_ptr<icore> _core;
    accept_cb_signature _accept_functor;
};
#endif // ASYNC_SERVER_H
