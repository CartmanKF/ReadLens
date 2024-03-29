// User.h
#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include "OCR.h"

class User {
protected:
    std::string username;
    std::string password;
    OCR ocr;

public:
    virtual void get_username() = 0;
    virtual void get_password() = 0;
    virtual bool login() = 0;
    virtual std::string getName() const;
    virtual OCR& getOCR();
    virtual std::vector<std::string> getCreatedTexts() const;
    virtual ~User() {}

    void listenToCreatedTexts();
};

#endif
