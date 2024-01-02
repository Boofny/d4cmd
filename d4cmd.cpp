#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cstdio>

namespace fs = std::filesystem;

int main() {
    std::string command;

    while (true) {
        fs::path currentDirectory = fs::current_path();

        std::cout << fs::current_path() << ">";
        std::getline(std::cin, command);

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

        if (commandName == "start") {
            std::string openCommand = commandName + " " + instruction;
            std::system(openCommand.c_str());
        }

        if (commandName == "echo") {
            std::cout << instruction << '\n';
        }

        if (command == "cls") {
            std::system(command.c_str());
        }

        if (command == "dir") {
            try {
                for(const auto& entry : fs::directory_iterator(fs::current_path())) {
                    std::cout << entry.path().filename() << '\n';
                }
            } catch (const fs::filesystem_error& e) {
                std::cout << "Error accessing directory: " << e.what() << '\n';
            }
        }

        if (commandName == "writeto") {
            std::string messagePosition = command.substr(command.find(" ", whitespacePosition + 1));
            messagePosition = messagePosition.substr(1);
            std::string fileName = instruction.substr(0, whitespacePosition + 1);
            
            std::ofstream file(fileName, std::ios::app);

            if (file.is_open()) {
                file << messagePosition << '\n';

                file.close();
                std::cout << "Data successfully written to file.\n";
            } else {
                std::cerr << "Trouble opening file: " << fileName << '\n';
            }
        }

        if (commandName == "delete") {
            if (std::remove(instruction.c_str()) == 0) {
                std::cout << instruction << " deleted successfully.\n";
            } else {
                std::cerr << "Trouble deleting file: " << instruction << '\n';
            }
        }

        if (commandName == "copy") {
            std::size_t position = instruction.find(" ");
            std::string destinationOfFile = instruction.substr(0, position);
            std::string destinationToCopyFile = instruction.substr(position + 1);


            std::size_t lastBackslashPosition = destinationOfFile.find_last_of("\\");
            std::string fileName = destinationOfFile.substr(lastBackslashPosition + 1);
            std::size_t dotPosition = fileName.find_last_of(".");
            fileName.insert(dotPosition, "_copy");

            try {
                fs::path pathToCopy = destinationOfFile;
                fs::path pathToCopyTo = destinationToCopyFile;

                fs::copy(pathToCopy, pathToCopyTo / fileName, fs::copy_options::recursive);

                std::cout << "File copied successfully.\n";
            } catch (const fs::filesystem_error& e) {
                std::cout << "Trouble copying file: " << e.what() << '\n';
            }
        }
    }

    return 0;
}
