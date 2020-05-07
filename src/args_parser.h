#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/parsers.hpp>

#include <optional>

namespace bpo = boost::program_options;

/**
 * @brief Класс парсинга аргументов командной строки
 */
class args_parser
{
public:
    /**
     * @brief Конструктор
     */
    args_parser();

    /**
     * @brief Метод парсинга
     * @arg argc - количество аргументов
     * @arg argv - массив строк аргументов
     * @return Размер блока команд
     */
    std::optional<unsigned short> parse(int argc, char** argv);

private:
    bpo::options_description _description;
    bpo::variables_map _values_storage;
};

#endif // ARGS_PARSER_H
