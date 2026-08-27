//
// Created by evgen on 27.08.2026.
//

#ifndef BULK_CONSOLE_OBSERVER_H
#define BULK_CONSOLE_OBSERVER_H
#include "i_observer.h"
#include <iostream>

/**
 * @brief Наблюдатель, выводящий содержимое готового блока команд в stdout.
 */
class ConsoleObserver : public IObserver {
public:
    /**
     * @brief Печатает команды блока в одну строку через пробел.
     * @param commands Команды блока.
     */
    void OnBlockComplete(const std::vector<std::string> &commands, time_t) override {
        std::cout << "bulk: ";
        for (const auto &item: commands) {
            std::cout << item << ' ';
        }
        std::cout << std::endl;
    }

    ~ConsoleObserver() override = default;
};

#endif //BULK_CONSOLE_OBSERVER_H

