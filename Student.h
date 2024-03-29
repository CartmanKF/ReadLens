// Student.h
#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"

class Student : public User {
public:
    void get_username() override;
    void get_password() override;
    bool login() override;
};

#endif
