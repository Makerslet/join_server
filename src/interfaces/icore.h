#ifndef ICORE_H
#define ICORE_H

#include "itables_manager.h"
#include "iserver.h"

#include <memory>

class execution_unit;

/**
 * @brief Интерфейс ядра приложения
 */
class icore
{
public:
    virtual ~icore() = default;

    /**
     * @brief Метод, позволяющий получить менеджер таблиц
     * @return Менеджер таблиц
     */
    virtual std::shared_ptr<itables_manager> tables_manager() = 0;

    /**
     * @brief Метод добавления единицы исполнения
     * @param exec_unit - единица исполнения
     */
    virtual void add_command(std::unique_ptr<execution_unit>&& exec_unit) = 0;

    /**
     * @brief Метод запуска ядра приложения
     */
    virtual void start() = 0;

    /**
     * @brief Метод остановки ядра приложения
     */
    virtual void stop() = 0;
};

#endif // ICORE_H
