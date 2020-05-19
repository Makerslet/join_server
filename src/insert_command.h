#ifndef INSERT_COMMAND_H
#define INSERT_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

/**
 * @brief Класс команды для вставки строки в таблицу
 * Если таблица с заданным именем отсутствует, то такая
 * таблица создается
 */
class insert_command : public icommand
{
    using table_sptr = std::shared_ptr<table>;
public:
    /**
     * @brief Конструктор, принимающий имя таблицы и значения столбцов
     * @param table_name - имя таблицы
     * @param values - значения столбцов таблицы
     */
    insert_command(const std::string& table_name,
                   const std::vector<std::string>& values);

    std::optional<std::string> execute(const command_context& context) override;

private:
    /**
     * @brief Метод получения идентификатора
     * @return идентификатор
     */
    std::size_t extract_id();

private:
    std::string _table_name;
    std::vector<std::string> _values;
};

#endif // INSERT_COMMAND_H
