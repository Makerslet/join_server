#ifndef ICOMMAND_HANDLER_H
#define ICOMMAND_HANDLER_H

#include "icommand.h"

#include <memory>

/**
 * @brief Интерфейс обработчика команд
 */
class icommand_handler
{
public:
    virtual ~icommand_handler() = default;

    /**
     * @brief Метод добавления единицы исполнения
     * @param exec_unit - единица исполнения
     */
    virtual void push_command(std::unique_ptr<execution_unit>&& exec_unit) = 0;

    /**
     * @brief Метод запуска обработки команд
     */
    virtual void start_handling() = 0;

    /**
     * @brief Метод остановки обработки команд
     */
    virtual void stop_handling() = 0;
};

#endif // ICOMMAND_HANDLER_H
