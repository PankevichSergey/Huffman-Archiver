//
// Created by Sergey Pankevich on 06.10.2021.
//

#pragma once

#include <stdint.h>

class Code {
public:
    uint64_t code = 0;
    uint8_t length = 0;
    void DeleteLast();
    void AddLast(uint64_t bit);
};
