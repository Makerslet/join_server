#ifndef COMMAND_HANDLING_EXCEPTION_H
#define COMMAND_HANDLING_EXCEPTION_H

#include <stdexcept>

/**
 * @brief Класс исключения - ошибка во время обработки команды
 */
class command_handling_exception : public std::runtime_error
{
public:
    /**
     * @brief Конструктор, принимающий описание ошибки
     * @param error - описание ошибки
     */
    command_handling_exception(const std::string& error);
};

#endif // COMMAND_HANDLING_EXCEPTION_H
