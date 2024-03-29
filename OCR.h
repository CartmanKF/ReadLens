// OCR.h
#ifndef OCR_H
#define OCR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

void SpeakTextFromFile(const std::string& filePath);

class OCR {
protected:
    int i;

public:
    std::string file_name;
    std::vector<std::string> createdTexts;

    void set_i(int i, const std::string& username);
    int return_i() const;
    void performOCR(const std::string& imagePath);
    std::vector<std::string> getCreatedTexts() const;
};

#endif
