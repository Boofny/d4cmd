#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main() {
    std::string command;

    while (true) {
        std::cout << fs::current_path() << '\n';
        std::getline(std::cin, command);

        if (command == "quit") break;

    }
    return 0;
}