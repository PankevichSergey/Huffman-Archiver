//
// Created by Sergey Pankevich on 06.10.2021.
//

#include "Code.h"

void Code::AddLast(uint64_t bit) {
    code += bit << length;
    ++length;
}

void Code::DeleteLast() {
    if ((code >> length) & 1) {
        code ^= 1 << length;
    }
    --length;
}