// Instructor.h
#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "User.h"


class Instructor : public User {
public:
    void get_username() override;
    void get_password() override;
    bool login() override;
    void addNotesToStudentFile(const std::string& studentFileName);
    void viewAllUsersTexts(const std::vector<User*>& users);
};

#endif
