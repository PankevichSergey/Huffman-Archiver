//
// Created by Sergey Pankevich on 06.10.2021.
//

#pragma once

#include <stdint.h>

class Code {
public:
    uint16_t code = 0;
    uint16_t length = 0;
    void DeleteLast();
    void AddLast(uint16_t bit);
};
