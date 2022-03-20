//
// Created by Sergey Pankevich on 04.10.2021.
//

#pragma once

#include <stdint.h>

#include <fstream>
#include <string_view>

const uint16_t FILENAME_END = 256;
const uint16_t ONE_MORE_FILE = 257;
const uint16_t ARCHIVE_END = 258;
const uint16_t MAX_SYMBOLS = 259;
const uint8_t BITS_IN_BLOCK = 9;
const uint8_t BITS_IN_CHAR = 8;
const uint8_t BUFFER_SIZE = 9;

std::ofstream OpenForWriting(std::string_view name);
std::ifstream OpenForReading(std::string_view name);