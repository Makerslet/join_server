#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include "interfaces/icommand_handler.h"
#include "interfaces/execution_unit.h"
#include "commands_queue.h"

#include <thread>

/**
 * @brief Класс обработки комманд.
 * Команды обрабатываются в отдельных потоках-воркерах
 */
class command_handler : public icommand_handler
{
    using worker_handler = std::function<void()>;
public:
    /**
     * @brief Конструктор, принимающий число потоков, в которых будет
     * происходить обработка комманд
     * @param num_workers - число потоков-воркеров
     */
    command_handler(std::size_t num_workers);

    void push_command(std::unique_ptr<execution_unit>&&) override;
    void start_handling() override;
    void stop_handling() override;

private:
    /**
     * @brief Метод-генератор лямбды-исполнителя команд,
     * передаваемой для работы в потоке
     * @return Лябда-обработчик команд
     */
    worker_handler create_worker_handler();

private:
    std::size_t _num_workers;
    std::vector<std::thread> _workers;
    queue_mt<std::unique_ptr<execution_unit>> _cmds_queue;
};

#endif // COMMAND_HANDLER_H
