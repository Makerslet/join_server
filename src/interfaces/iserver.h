#ifndef ISERVER_H
#define ISERVER_H

/**
 * @brief Интерфейс сервера
 */

class iserver
{
public:
    virtual ~iserver() = default;

    /**
     * @brief Метод запуска сервера
     */
    virtual void start() = 0;

    /**
     * @brief Метод остановки сервера
     */
    virtual void stop() = 0;
};

#endif // ISERVER_H
