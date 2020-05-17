#ifndef SIGNALS_HANDLER_H
#define SIGNALS_HANDLER_H

#include "interfaces/icore.h"

#include <boost/system/error_code.hpp>
#include <functional>

/**
 * @brief Класс содержащий генератор колбека для обработки сигнала SIGINT
 */
class signals_handler
{
    using sig_handler_signature = std::function<void(const boost::system::error_code&, int)>;
public:
    /**
     * @brief Генератор обработчика сигнала (SIGINT)
     * @arg core - ядро приложения
     * @arg server - сервер приложения
     */
    static sig_handler_signature create_sigs_handler(
            std::shared_ptr<icore> core,
            std::shared_ptr<iserver> server);
};

#endif // SIGNALS_HANDLER_H
