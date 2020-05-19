#ifndef ITABLES_MANAGER_H
#define ITABLES_MANAGER_H

#include "../table.h"

#include <string>

/**
 * @brief Интерфейс менеджера таблиц
 */
class itables_manager
{
public:
    virtual ~itables_manager() = default;

    /**
     * @brief Метод позволяет проверить содержится ли указанная таблица
     * @param name - имя таблицы
     * @return Содержится ли указанная таблица
     */
    virtual bool contain_table(const std::string& table_name) = 0;

    /**
     * @brief Метод добавления таблицы с указанным именем
     * @param name - имя таблицы
     * @return Таблица
     */
    virtual std::shared_ptr<table> add_table(const std::string& table_name) = 0;

    /**
     * @brief Метод получения таблицы
     * @param table_name - имя таблицы
     * @return Таблица
     */
    virtual std::shared_ptr<table> get_table(const std::string& table_name) = 0;

    /**
     * @brief Метод удаления таблицы
     * @param table_name - имя таблицы
     */
    virtual void remove_table(const std::string& table_name) = 0;
};

#endif // ITABLES_MANAGER_H
