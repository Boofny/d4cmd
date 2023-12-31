#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

int main() {
    std::string command;

    while (true) {
        fs::path currentDirectory = fs::current_path();

        beginning:std::cout << fs::current_path() << ">";
        std::getline(std::cin, command);

        for (char& c : command) {
            c = tolower(c);
        }

        if (command == "quit") break;

        std::size_t whitespacePosition = command.find(" ");
        std::string commandName = command.substr(0, whitespacePosition);
        std::string instruction = command.substr(whitespacePosition + 1);

        if (commandName == "cd") {
            fs::path newPath;
            if (instruction == "..") {
                newPath = fs::current_path().parent_path();
                try {
                    if (fs::exists(newPath) && fs::is_directory(newPath)) {
                        fs::current_path(newPath);
                    }
                } catch (fs::filesystem_error& e) {
                    std::cerr << "Directory not found or not valid directory: " << e.what() << '\n';
                }
            }

            newPath = currentDirectory / instruction;
            try {
                if (fs::exists(newPath) && fs::is_directory(newPath)) {
                    fs::current_path(newPath);
                }
            } catch (const fs::filesystem_error& e) {
                std::cerr << "Directory not found or not valid directory: " << e.what() << '\n';
            }
        }

        if (commandName == "mkfile") {
            std::ofstream file(instruction);

            if (file.is_open()) {
                std::cout << "File successfully created.\n";
                file.close();
            } else {
                std::cerr << "Error creating file: " << instruction << '\n';
            }
        }

        if (commandName == "mkdir") {
            std::string currentPath = fs::current_path().string();
            std::string append = currentPath + "\\" + instruction;
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
