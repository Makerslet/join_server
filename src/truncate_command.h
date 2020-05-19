#ifndef TRUNCATE_COMMAND_H
#define TRUNCATE_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

/**
 * @brief Класс команды для удаления таблицы
 */
class truncate_command : public icommand
{
public:
    /**
     * @brief Конструктор принимающий имя таблицы
     * @param table_name - имя таблицы
     */
    truncate_command(const std::string& table_name);
    std::optional<std::string> execute(const command_context& context) override;

private:
    std::string _table_name;
};

#endif // TRUNCATE_COMMAND_H
