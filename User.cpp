// User.cpp
#include "User.h"

std::string User::getName() const {
    return username;
}

OCR& User::getOCR() {
    return ocr;
}

std::vector<std::string> User::getCreatedTexts() const {
    return ocr.getCreatedTexts();
}

void User::listenToCreatedTexts() {
    std::vector<std::string> userTexts = getCreatedTexts();

    if (userTexts.empty()) {
        std::cout << "No created texts to listen to." << std::endl;
        return;
    }

    std::cout << "Previously created texts:" << std::endl;
    for (int i = 0; i < userTexts.size(); ++i) {
        std::cout << i + 1 << ". " << userTexts[i] << std::endl;
    }

    int selectedTextIndex;
    std::cout << "Select the text to listen to (enter the corresponding number): ";

    while (true) {
        std::cin >> selectedTextIndex;

        if (std::cin.fail() || selectedTextIndex < 1 || selectedTextIndex > userTexts.size()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a valid number." << std::endl;
            std::cout << "Select the text to listen to (enter the corresponding number): ";
        }
        else {
            break; // Valid input, exit the loop
        }
    }

    if (selectedTextIndex >= 1 && selectedTextIndex <= userTexts.size()) {
        SpeakTextFromFile(userTexts[selectedTextIndex - 1]);
    }
    else {
        std::cout << "Invalid selection." << std::endl;
    }
}
