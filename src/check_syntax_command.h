#ifndef CHECK_SYNTAX_COMMAND_H
#define CHECK_SYNTAX_COMMAND_H

#include "interfaces/icommand.h"
#include "interfaces/icore.h"
#include "session.h"

/**
 * @brief Команда проверки синтаксической корректности запроса
 */
class check_syntax_command : public icommand
{
public:
    /**
     * @brief Конструктор
     * @param request - текст запроса
     */
    check_syntax_command(const std::string& request);

    /**
     * @brief Метод исполнения комманды
     * @param context - контекст исполнения команды
     * @return результат выполнения команды
     */
    std::optional<std::string> execute(const command_context& context) override;

private:
    /**
     * @brief Метод удаления пустых токенов
     * @param tokens - вектор токенов запроса
     */
    void erase_empty_tokens(std::vector<std::string>& tokens);

    /**
     * @brief Проверка запроса вставки и генерация соответствующей комманды для обработки
     * @param tokens - вектор токенов запроса
     * @param context - контекст исполнения команды
     */
    void handle_insert(const std::vector<std::string>& tokens,
                       const command_context& context);

    /**
     * @brief Проверка запроса удаления и генерация соответствующей комманды для обработки
     * @param tokens - вектор токенов запроса
     * @param context - контекст исполнения команды
     */
    void handle_truncate(const std::vector<std::string>& tokens,
                         const command_context& context);

    /**
     * @brief Проверка запроса пересечения и генерация соответствующей комманды для обработки
     * @param tokens - вектор токенов запроса
     * @param context - контекст исполнения команды
     */
    void handle_intersection(const std::vector<std::string> &tokens,
                             const command_context& context);

    /**
     * @brief Проверка запроса симметричной разницы и генерация соответствующей комманды для обработки
     * @param tokens - вектор токенов запроса
     * @param context - контекст исполнения команды
     */
    void handle_symmetric_difference(const std::vector<std::string> &tokens,
                                     const command_context& context);
private:
    std::string _request;
};

#endif // CHECK_SYNTAX_COMMAND_H
