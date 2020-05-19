#ifndef SYMMETRIC_DIFFERENCE_COMMAND_H
#define SYMMETRIC_DIFFERENCE_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

/**
 * @brief Класс команды для обработки запроса симметричную разницу двух таблиц
 */
class symmetric_difference_command : public icommand
{
public:
    /**
     * @brief Конструктор, принимающий имена таблиц
     * @param table1_name - имя первой таблицы
     * @param table2_name - имя второй таблицы
     */
    symmetric_difference_command(const std::string& table1_name,
                                 const std::string& table2_name);

    std::optional<std::string> execute(const command_context& context) override;

private:
    /**
     * @brief Метод преобразования результата пересечения в строку
     * @param rows - строки полученные в результате пересечения
     * @return тестовое представление
     */
    std::string to_string(const std::vector<table::sym_diff_row>& rows);

private:
    std::string _table1_name;
    std::string _table2_name;
};

#endif // SYMMETRIC_DIFFERENCE_COMMAND_H
