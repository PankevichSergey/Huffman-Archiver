//
// Created by Sergey Pankevich on 10.10.2021.
//

#include "input_output.h"

std::ofstream OpenForWriting(std::string_view name) {
    std::ofstream output;
    output.open(name);
    if (!output.is_open()) {
        throw std::invalid_argument("can't open file for writing");
    }
    return output;
}

std::ifstream OpenForReading(std::string_view name) {
    std::ifstream input;
    input.open(name);
    if (!input.is_open()) {
        throw std::invalid_argument("can't open file for reading");
    }
    return input;
}