// Instructor.cpp
#include "Instructor.h"
#include <iostream>
#include "User.h" 

void Instructor::get_username() {
    std::cout << "Enter instructor username: ";
    std::cin >> username;
}

void Instructor::get_password() {
    std::cout << "Enter instructor password: ";
    std::cin >> password;
}

bool Instructor::login() {
    std::string inputPassword;
    std::cout << "Enter Instructor password: ";
    std::cin >> inputPassword;
    return (inputPassword == password);
}

void Instructor::addNotesToStudentFile(const std::string& studentFileName) {
    std::ifstream inFile(studentFileName);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open file for reading." << std::endl;
        return;
    }

    std::string currentLine;
    std::vector<std::string> fileContent;

    while (getline(inFile, currentLine)) {
        fileContent.push_back(currentLine);
    }

    inFile.close();

    std::cout << "Current notes in the file:" << std::endl;
    for (const std::string& line : fileContent) {
        std::cout << line << std::endl;
    }

    std::cout << "Enter the notes to add (enter 'exit' to finish):" << std::endl;
    std::string newNote;
    while (true) {
        getline(std::cin, newNote);
        if (newNote == "exit") {
            break;
        }
        fileContent.push_back(newNote);
    }

    std::ofstream outFile(studentFileName);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return;
    }

    for (const std::string& line : fileContent) {
        outFile << line << std::endl;
    }

    outFile.close();

    std::cout << "Notes added to the file successfully." << std::endl;
}

void Instructor::viewAllUsersTexts(const std::vector<User*>& users) {
    std::cout << "Viewing all users' created texts:" << std::endl;
    std::cout << "------------------------------------" << std::endl;
    for (const User* user : users) {
        std::cout << "User: " << user->getName() << std::endl;
        std::vector<std::string> userTexts = user->getCreatedTexts();
        for (const std::string& text : userTexts) {
            std::cout << text << std::endl;
        }
        std::cout << "------------------------------------" << std::endl;
    }
}
