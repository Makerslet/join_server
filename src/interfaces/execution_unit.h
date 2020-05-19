#ifndef EXECUTION_UNIT_H
#define EXECUTION_UNIT_H

#include "icommand.h"
#include <memory>

/**
 * @brief Класс, описывающий единицу исполнения. Содержит
 * саму команду, подлежащую исполнению и контекст исполнения.
 */
struct execution_unit
{
    /**
     * @brief Конструктор, принимающий команду и контекст исполнения
     * @param cmd - команда
     * @param context - контекст исполнения команды
     */
    execution_unit(std::unique_ptr<icommand>&& cmd, command_context context) :
        command(std::move(cmd)), context(context)
    {}

    std::unique_ptr<icommand> command;
    command_context context;
};

#endif // EXECUTION_UNIT_H
