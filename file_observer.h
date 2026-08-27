//
// Created by evgen on 27.08.2026.
//

#ifndef BULK_FILE_OBSERVER_H
#define BULK_FILE_OBSERVER_H
#include "i_observer.h"

#include <fstream>
#include <iostream>

/**
 * @brief Наблюдатель, сохраняющий содержимое готового блока команд в файл.
 *
 * Имя файла формируется как bulk<timestamp>.log, где timestamp — время
 * получения первой команды блока. Один файл создаётся на один блок.
 */
class FileObserver : public IObserver {
public:
    /**
     * @brief Записывает команды блока в новый файл bulk<t>.log.
     * @param commands Команды блока.
     * @param t Время получения первой команды блока (используется в имени файла).
     */
    void OnBlockComplete(const std::vector<std::string> &commands, const time_t t) override {
        const auto filename = std::string("bulk") + std::to_string(t) + std::string(".log");
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Couldn't open file: " << filename << std::endl;
            return;
        }
        file << "bulk: ";
        for (auto &command : commands) {
            file << command << ' ';
        }
        file << "\n";
    }
    ~FileObserver() override = default;
};

#endif //BULK_FILE_OBSERVER_H