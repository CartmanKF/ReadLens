// OCR.cpp
#include "OCR.h"




void OCR::set_i(int i, const std::string& username) {
    this->i = i;
    file_name = username + "_temp" + std::to_string(i) + ".txt";
}

int OCR::return_i() const {
    return i+1;
}

void OCR::performOCR(const std::string& imagePath) {
    Pix* image = pixRead(imagePath.c_str());

    if (!image) {
        std::cerr << "Error: Unable to load image." << std::endl;
        return;
    }

    tesseract::TessBaseAPI tess;
    tess.Init(nullptr, "eng");

    tess.SetImage(image);

    char* outText = tess.GetUTF8Text();
    std::cout << "Text :\n" << outText << std::endl;

    std::ofstream outFile(file_name);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        pixDestroy(&image);
        delete[] outText;
        return;
    }
    outFile << outText;
    outFile.close();

    SpeakTextFromFile(file_name);

    createdTexts.push_back(file_name);

    delete[] outText;
    pixDestroy(&image);
}

std::vector<std::string> OCR::getCreatedTexts() const {
    return createdTexts;
}
