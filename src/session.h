#ifndef SESSION_H
#define SESSION_H

#include "interfaces/icore.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>

#include <memory>
#include <functional>

namespace bio = boost::asio;

class session : public std::enable_shared_from_this<session>
{
    /**
     * @brief Алиас на сигнатуру коллбека для чтения
     */
    using read_cb_signature = std::function<void(boost::system::error_code ec, std::size_t length)>;
public:

    /**
     * @brief Конструктора
     * @param socket - сокет клиента
     * @param core - ядро приложения
     */
    session(bio::ip::tcp::socket socket,
            std::shared_ptr<icore> core);

    /**
     * @brief Метод запуска цикла работы с клиентом
     */
    void start();

private:

    /**
     * @brief Метод запуска асинхронного чтения
     */
    void read();

    /**
     * @brief Метод обработки запроса от пользователя
     */
    void handle_request(std::string request);

    /**
     * @brief Метод обработки отключения пользователя
     */
    void finish_handling();

    /**
     * @brief Метод генерации лямбды-обработчика чтения из сокета
     */
    read_cb_signature create_read_lambda();

private:
    bio::ip::tcp::socket _socket;
    std::shared_ptr<icore> _core;

    read_cb_signature _read_callback;
    std::array<char, 1500> _buffer;
};

#endif // SESSION_H
