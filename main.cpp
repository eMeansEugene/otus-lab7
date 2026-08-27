#include <iostream>
#include "accumulator.h"
#include "console_observer.h"
#include "file_observer.h"

void RunLoop(std::istream &input, Accumulator &acc) {
    std::string line;
    while (std::getline(input, line)) {
        acc.ProcessCommand(line);
    }
    acc.HandleEof();
}

int main(const int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <bulk_size>" << std::endl;
        return 1;
    }

    size_t bulk_size = 0;
    try {
        bulk_size = std::stoul(argv[1]);
        if (bulk_size == 0 || argv[1][0] == '-') {
            std::cerr << "Bulk size must be positive" << std::endl;
            return 1;
        }
    } catch (const std::exception &) {
        std::cerr << "Invalid bulk size: " << argv[1] << std::endl;
        return 1;
    }
    Accumulator accumulator(bulk_size);
    accumulator.AddObserver(std::make_shared<ConsoleObserver>());
    accumulator.AddObserver(std::make_shared<FileObserver>());
    RunLoop(std::cin, accumulator);
    return 0;
}
