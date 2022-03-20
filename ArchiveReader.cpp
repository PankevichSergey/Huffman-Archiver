//
// Created by Sergey Pankevich on 04.10.2021.
//

#include "ArchiveReader.h"

ArchiveReader::ArchiveReader(std::istream& input) : buffer_(0), read_bits_(BITS_IN_CHAR), input_(input) {}

void ArchiveReader::ReadToBuffer() {
    read_bits_ = 0;
    char ch;
    input_.get(ch);
    if (input_.eof()) {
        buffer_ = 0;
    } else {
        buffer_ = ch;
    }
}

bool ArchiveReader::Read1Bit() {
    if (read_bits_ == BITS_IN_CHAR) {
        ReadToBuffer();
    }
    ++read_bits_;
    return (buffer_ >> (read_bits_ - 1)) & 1;
}

uint16_t ArchiveReader::Read9Bits() {
    uint16_t result = 0;
    for (uint8_t i = 0; i < 9; ++i) {
        result ^= static_cast<uint8_t>(Read1Bit()) << i;
    }
    return result;
}
