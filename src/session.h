#ifndef SESSION_H
#define SESSION_H

#include "interfaces/icore.h"

#include <boost/asio/ip/tcp.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio/streambuf.hpp>

#include <memory>
#include <functional>

namespace bio = boost::asio;

/**
 * @brief Класс сессии работы с пользователем
 */
class session : public std::enable_shared_from_this<session>
{
    /**
     * @brief Алиас на сигнатуру коллбека для чтения
     */
    using read_cb_signature = std::function<void(boost::system::error_code ec, std::size_t length)>;

    /**
     * @brief Алиас на сигнатуру коллбека для записи
     */
    using write_cb_signature = std::function<void(boost::system::error_code ec, std::size_t length)>;
public:

    /**
     * @brief Конструктор
     * @param socket - сокет клиента
     * @param core - ядро приложения
     */
    session(bio::ip::tcp::socket socket,
            std::shared_ptr<icore> core);

    /**
     * @brief Метод запуска цикла работы с клиентом
     */
    void start();

    /**
     * @brief Метод отправки данных клиенту
     */
    void send(const std::string& message);

private:

    /**
     * @brief Метод запуска асинхронного чтения
     */
    void read();

    /**
     * @brief Метод обработки отключения пользователя
     */
    void finish_handling();

    /**
     * @brief Метод генерации лямбды-обработчика чтения из сокета
     */
    read_cb_signature create_read_lambda();

    /**
     * @brief Метод генерации лямбды-обработчика записи в сокет
     */
    read_cb_signature create_write_lambda();

    /**
     * @brief Метод очищения буффера
     */
    void clear_buffer();

private:
    bio::ip::tcp::socket _socket;
    std::shared_ptr<icore> _core;

    bio::streambuf _read_buffer;
    std::istream _input_stream;

    bio::streambuf _write_buffer;
    std::ostream _output_stream;
    bool _is_sending;

    read_cb_signature _read_callback;
    write_cb_signature _write_callback;
};

#endif // SESSION_H
