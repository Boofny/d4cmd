#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

int main() {
    std::string command;
    std::string path = "";

    while (true) {
        path = fs::current_path().string();
        
        beginning:std::cout << path << ">";
        std::getline(std::cin, command);

        for (char& c : command) {
            c = tolower(c);
        }

        if (command == "quit") break;

        std::size_t whitespacePosition = command.find(" ");
        std::string commandName = command.substr(0, whitespacePosition);
        std::string instruction = command.substr(whitespacePosition + 1);

        if (commandName == "mkdir") {
            std::string append = path + "\\" + instruction;
            try {
                fs::create_directory(append);

                std::cout << instruction << " created successfully.\n";
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Error creating " << instruction << ": " << e.what() << '\n';
            }
        }


    }
    return 0;
}