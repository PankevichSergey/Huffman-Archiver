//
// Created by Sergey Pankevich on 05.10.2021.
//

#pragma once

#include <queue>

#include "TrieNode.h"

struct Element {
    size_t priority;
    TrieNode* value;
    Element(size_t priority, TrieNode* value);
    Element(const Element& lhs, const Element& rhs);
    bool operator<(const Element& other) const;
};

struct HeapNode {
    HeapNode* left = nullptr;
    HeapNode* right = nullptr;
    Element value;
    uint16_t size = 0;
    HeapNode(const Element& element);
};

class Heap {
public:
    Heap() = default;
    ~Heap();
    uint16_t Size() const;
    const Element& Top() const;
    void Pop();
    void Push(const Element& element);

private:
    void DeleteDfs(HeapNode* node);
    void AddNode(HeapNode*& was, HeapNode* added);
    HeapNode* Merge(HeapNode* left, HeapNode* right);
    uint16_t GetSize(HeapNode* node) const;
    void UpdateSize(HeapNode* node);
    HeapNode* root_ = nullptr;
};