//
// Created by Sergey Pankevich on 05.10.2021.
//

#include "TrieNode.h"

TrieNode::TrieNode(uint16_t _value) {
    value = _value;
    to[0] = to[1] = nullptr;
}

TrieNode::TrieNode(TrieNode* zero, TrieNode* one) {
    to[0] = zero;
    to[1] = one;
}

bool TrieNode::IsTerminal() {
    return to[0] == nullptr && to[1] == nullptr;
}