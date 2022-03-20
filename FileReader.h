//
// Created by Sergey Pankevich on 06.10.2021.
//
#pragma once

#include <istream>

class FileReader {
public:
    FileReader(std::istream& input);
    void ReadChar();
    bool HaveCharsToRead();
    uint8_t GetChar();

private:
    char read_char_;
    std::istream& input_;
};
