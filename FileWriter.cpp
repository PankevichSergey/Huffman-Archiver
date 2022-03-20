//
// Created by Sergey Pankevich on 06.10.2021.
//

#include "FileWriter.h"

FileWriter::FileWriter(std::ostream& output) : output_(output) {}

void FileWriter::WriteChar(uint8_t ch) {
    output_ << ch;
}

void FileWriter::Flush() {
    output_.flush();
}