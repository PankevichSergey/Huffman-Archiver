//
// Created by Sergey Pankevich on 05.10.2021.
//

#include "Heap.h"

Element::Element(size_t priority, TrieNode* value) : priority(priority), value(value) {
}

Element::Element(const Element& lhs, const Element& rhs) {
    priority = lhs.priority + rhs.priority;
    value = new TrieNode(lhs.value, rhs.value);
}

bool Element::operator<(const Element& other) const {
    return priority > other.priority;
}

uint16_t Heap::Size() const {
    return GetSize(root_);
}

HeapNode::HeapNode(const Element& element) : value(element) {
}

const Element& Heap::Top() const {
    if (root_ == nullptr) {
        throw std::logic_error("trying to access top element in empty heap");
    }
    return root_->value;
}

uint16_t Heap::GetSize(HeapNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    return node->size;
}

void Heap::UpdateSize(HeapNode* node) {
    node->size = GetSize(node->left) + 1 + GetSize(node->right);
}
void Heap::AddNode(HeapNode*& was, HeapNode* added) {
    if (was == nullptr) {
        std::swap(was, added);
    } else {
        if (added->value.priority < was->value.priority) {
            std::swap(was->value, added->value);
        }
        if (GetSize(was->left) < GetSize(was->right)) {
            AddNode(was->left, added);
        } else {
            AddNode(was->right, added);
        }
    }
    UpdateSize(was);
}

void Heap::Push(const Element& element) {
    HeapNode* node = new HeapNode(element);
    AddNode(root_, node);
}

HeapNode* Heap::Merge(HeapNode* left, HeapNode* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->value.priority < right->value.priority) {
        if (GetSize(left->left) < GetSize(left->right)) {
            left->left = Merge(left->left, right);
        } else {
            left->right = Merge(left->right, right);
        }
        UpdateSize(left);
        return left;
    } else {
        if (GetSize(right->left) < GetSize(right->right)) {
            right->left = Merge(left, right->left);
        } else {
            right->right = Merge(left, right->right);
        }
        UpdateSize(right);
        return right;
    }
}

void Heap::Pop() {
    if (root_ == nullptr) {
        throw std::logic_error("trying to pop from empty heap");
    }
    HeapNode* left = root_->left;
    HeapNode* right = root_->right;
    delete root_;
    root_ = Merge(left, right);
}

void Heap::DeleteDfs(HeapNode* node) {
    if (node == nullptr) {
        return;
    }
    DeleteDfs(node->left);
    DeleteDfs(node->right);
    delete node;
}

Heap::~Heap() {
    DeleteDfs(root_);
}