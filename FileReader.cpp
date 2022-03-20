//
// Created by Sergey Pankevich on 06.10.2021.
//

#include "FileReader.h"

FileReader::FileReader(std::istream& input) : input_(input) {}

void FileReader::ReadChar() {
    input_.get(read_char_);
}

bool FileReader::HaveCharsToRead() {
    return !input_.eof();
}

uint8_t FileReader::GetChar() {
    return read_char_;
}
