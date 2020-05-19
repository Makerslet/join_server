#ifndef ICOMMAND_H
#define ICOMMAND_H

#include "../session.h"
#include "icore.h"

#include <string>
#include <optional>
#include <memory>

/**
 * @brief Класс, описывающий контекст исполнения команды
 */
struct command_context
{
    std::shared_ptr<session> sess;
    std::shared_ptr<icore> core;
};

/**
 * @brief Интерфейс команды. Позволяет выполнить команду
 */
class icommand
{
public:
    /**
     * @brief Деструктор
     */
    virtual ~icommand() = default;

    /**
     * @brief Метод исполнения команды. Для исполнения требуется объект
     * контекста. В качестве результата может быть возвращена строка
     * @param context - контекст исполнения команды
     * @return результат исполнения команды
     */
    virtual std::optional<std::string> execute(const command_context& context) = 0;
};

#endif // ICOMMAND_H
