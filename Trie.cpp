//
// Created by Sergey Pankevich on 05.10.2021.
//

#include "Trie.h"

#include <algorithm>
#include <iostream>

#include "Heap.h"

Trie::Trie(const FrequencyTable& frequency) {
    Heap heap;
    for (const auto& [ch, count] : frequency) {
        heap.Push(Element(count, new TrieNode(ch)));
    }
    while (heap.Size() > 1) {
        Element right = heap.Top();
        heap.Pop();
        Element left = heap.Top();
        heap.Pop();
        heap.Push(Element(left, right));
    }
    root_ = heap.Top().value;
}

Trie::Trie(const Canonic& canonic) {
    root_ = new TrieNode();
    std::vector<TrieNode*> current_depth;

    current_depth.push_back(root_->to[0] = new TrieNode());
    current_depth.push_back(root_->to[1] = new TrieNode());
    uint16_t added_chars = 0;
    for (uint8_t length = 1; length <= canonic.count_codes_of_length.size(); ++length) {
        std::vector<TrieNode*> next_depth;
        std::reverse(current_depth.begin(), current_depth.end());
        for (uint16_t i = 0; i < canonic.count_codes_of_length[length - 1]; ++i) {
            current_depth.back()->value = canonic.order[added_chars++];
            current_depth.pop_back();
        }
        while (!current_depth.empty()) {
            next_depth.push_back(current_depth.back()->to[0] = new TrieNode());
            next_depth.push_back(current_depth.back()->to[1] = new TrieNode());
            current_depth.pop_back();
        }
        current_depth = next_depth;
    }
}

Trie::Canonic Trie::GetCanonicForm() const {
    std::unordered_map<uint16_t, uint8_t> code_lengths;
    std::function<void(TrieNode*, uint8_t)> Dfs = [&code_lengths, &Dfs](TrieNode* vertex, uint8_t depth) {
        if (vertex->IsTerminal()) {
            code_lengths[vertex->value] = depth;
            return;
        }
        for (uint8_t bit = 0; bit <= 1; ++bit) {
            Dfs(vertex->to[bit], depth + 1);
        }
    };
    Dfs(root_, 0);
    Canonic canonic;
    for (const auto& [ch, length] : code_lengths) {
        if (canonic.count_codes_of_length.size() < length) {
            canonic.count_codes_of_length.resize(length, 0);
        }
        ++canonic.count_codes_of_length[length - 1];
        canonic.order.push_back(ch);
    }
    std::sort(canonic.order.begin(), canonic.order.end(),
              [&code_lengths](uint16_t lhs, uint16_t rhs) { return code_lengths[lhs] < code_lengths[rhs]; });
    return canonic;
}

Trie::CodesTable Trie::GetCodesTable() const {
    CodesTable codes_table;
    Code code;
    std::function<void(TrieNode*)> Dfs = [&codes_table, &code, &Dfs](TrieNode* vertex) {
        if (vertex->IsTerminal()) {
            codes_table[vertex->value] = code;
            return;
        }
        for (uint8_t bit = 0; bit <= 1; ++bit) {
            code.AddLast(bit);
            Dfs(vertex->to[bit]);
            code.DeleteLast();
        }
    };
    Dfs(root_);
    return codes_table;
}

void PrintDfs(TrieNode* v, std::string code = "") {
    if (v->IsTerminal()) {
        std::cout << static_cast<int>(v->value) << " : " << code << std::endl;
        return;
    }
    for (uint8_t bit = 0; bit <= 1; ++bit) {
        code += '0' + bit;
        PrintDfs(v->to[bit], code);
        code.pop_back();
    }
}

void Trie::Print() const {
    if (root_ != nullptr) {
        PrintDfs(root_);
    }
}

void Trie::DeleteDfs(TrieNode* vertex) {
    if (vertex == nullptr) {
        return;
    }
    DeleteDfs(vertex->to[0]);
    DeleteDfs(vertex->to[1]);
    delete vertex;
}

void Trie::MoveState(bool bit) {
    if (state_ == nullptr) {
        state_ = root_;
    }
    state_ = state_->to[bit];
    if (state_ == nullptr) {
        MoveState(bit);
    }
}

bool Trie::ReachedTerminal() {
    return state_->IsTerminal();
}

uint16_t Trie::GetStateValue() {
    return state_->value;
}

Trie::~Trie() {
    DeleteDfs(root_);
}