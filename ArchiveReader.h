//
// Created by Sergey Pankevich on 04.10.2021.
//

#pragma once
#include "input_output.h"

class ArchiveReader {
public:
    ArchiveReader(std::istream& input);
    uint16_t Read9Bits();
    bool Read1Bit();

private:
    void ReadToBuffer();
    unsigned char buffer_;
    uint8_t read_bits_;
    std::istream& input_;
};
