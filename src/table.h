#ifndef TABLE_H
#define TABLE_H

#include <boost/thread/shared_mutex.hpp>

#include <map>
#include <functional>

/**
 * @brief Класс описания таблицы фиксированного формата
 * 2 столбца, 0 столбец - ключевой и содержит целые числа,
 * 1 столбец содержит строки
 */
class table
{
public:
    using intersection_row = std::tuple<std::size_t, std::string, std::string>;
    using sym_diff_row = std::tuple<std::size_t, std::string, std::string>;

public:
    /**
     * @brief Конструктор
     */
    table();

    /**
     * @brief Конструктор копирования
     * @param arg - база
     */
    table(table& arg);

    /**
     * @brief Оператор сравнения
     * @param arg - вторая таблица
     */
    bool operator==(table& arg);

    /**
     * @brief Метод проверки пустоты таблицы
     * @return Пуста ли таблица
     */
    bool empty();

    /**
     * @brief Метод проверки наличия строки
     * @param id - идентификатор строки
     * @return Наличие строки
     */
    bool line_exists(std::size_t id);

    /**
     * @brief Метод получения значения в строке
     * @param id - идентификатор строки
     * @return Значение строки
     */
    std::string line_value(std::size_t id);

    /**
     * @brief Метод вставки строки
     * @param id - идентификатор строки
     * @param name - значение в строке
     * @return Осуществлена ли вставка
     */
    bool insert(std::size_t id, const std::string& name);

    /**
     * @brief Метод получения пересечения двух таблиц
     * @param table - вторая таблица
     * @return Результат пересечения
     */
    std::vector<intersection_row> intersection(const table& table);

    /**
     * @brief Метод получения симетричной разницы двух таблиц
     * @param table - вторая таблица
     * @return Результат симетричной разницы
     */
    std::vector<sym_diff_row> sym_diff(const table& table);

private:
    /**
     * @brief Метод получения содержимого таблицы
     * @return Содержимое таблицы
     */
    std::map<std::size_t, std::string> get_content();

private:
    boost::shared_mutex _rw_mutex;
    std::map<std::size_t, std::string> _table_content;
};

#endif // TABLE_H
