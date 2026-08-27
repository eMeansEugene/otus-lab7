//
// Created by evgen on 27.08.2026.
//

#ifndef BULK_I_OBSERVER_H
#define BULK_I_OBSERVER_H

#include <vector>
#include <string>

/**
 * @brief Интерфейс подписчика на события завершения блока команд.
 *
 * Реализации получают уведомление, когда Accumulator считает блок
 * команд полностью сформированным (по достижении размера блока,
 * по закрытию динамического блока или принудительно по EOF).
 * Accumulator не знает, как именно наблюдатель обрабатывает блок —
 * это обеспечивает низкую связанность между накоплением команд
 * и их выводом/сохранением.
 */
class IObserver {
public:
    /**
     * @brief Вызывается, когда блок команд готов к обработке.
     * @param commands Список команд блока в порядке поступления.
     * @param blockTime Время получения первой команды блока (unix timestamp).
     *        Не вызывается для пустых блоков.
     */
    virtual void OnBlockComplete(const std::vector<std::string> &commands, time_t blockTime) = 0;

    virtual ~IObserver() = default;
};
#endif //BULK_I_OBSERVER_H