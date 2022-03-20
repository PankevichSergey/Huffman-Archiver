//
// Created by Sergey Pankevich on 05.10.2021.
//

#pragma once

#include <unordered_map>
#include <vector>

#include "Code.h"
#include "Heap.h"
#include "TrieNode.h"

using FrequencyTable = std::unordered_map<uint16_t, size_t>;

class Trie {
public:
    struct Canonic {
        std::vector<uint16_t> order;
        std::vector<uint16_t> count_codes_of_length;
        Canonic() = default;
    };

    using CodesTable = std::unordered_map<uint16_t, Code>;

    Trie(const FrequencyTable& frequency);
    ~Trie();
    Canonic GetCanonicForm() const;
    Trie(const Canonic& canonic);
    CodesTable GetCodesTable() const;

    void MoveState(bool bit);
    bool ReachedTerminal();
    uint16_t GetStateValue();

    void Print() const;
private:
    void DeleteDfs(TrieNode* vertex);
    TrieNode* root_ = nullptr;
    TrieNode* state_ = nullptr;
};
