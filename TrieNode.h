//
// Created by Sergey Pankevich on 05.10.2021.
//

#pragma once

#include <stdint.h>

struct TrieNode {
    TrieNode* to[2];
    uint16_t value;
    TrieNode(uint16_t _value);
    TrieNode(TrieNode* zero, TrieNode* one);
    TrieNode() = default;
    bool IsTerminal();
};
