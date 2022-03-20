//
// Created by Sergey Pankevich on 06.10.2021.
//

#pragma once

#include <iostream>

class FileWriter {
public:
    FileWriter(std::ostream& output);
    void WriteChar(uint8_t ch);
    void Flush();

private:
    std::ostream& output_;
};
