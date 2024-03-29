// Student.cpp
#include "Student.h"
#include <iostream>
#include "User.h" 
void Student::get_username() {
    std::cout << "Enter student username: ";
    std::cin >> username;
}

void Student::get_password() {
    std::cout << "Enter student password: ";
    std::cin >> password;
}

bool Student::login() {
    std::string inputPassword;
    std::cout << "Enter student password: ";
    std::cin >> inputPassword;
    return (inputPassword == password);
}
