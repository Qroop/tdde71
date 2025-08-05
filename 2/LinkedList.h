#include <cstddef>
#include <string>

#pragma once

class LinkedList {
public:
    LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& other) noexcept;
    LinkedList& operator=(const LinkedList& other);
    LinkedList& operator=(LinkedList&& other) noexcept;
    ~LinkedList();

    void insert(int value);
    void push_back(int value);
    int pop_front();
    int pop_back();
    bool is_empty() const;
    int front() const;
    int back() const;
    int get(int index) const;
    void clear();
    int size() const;

    std::string to_string() const;
    void swap(int index1, int index2);

private:
    struct Node {
        Node(int val) : value(val), next(nullptr) {}
        int value;
        Node* next;
    };

    Node* head;
    Node* tail;
    int list_size;
};

void sort(LinkedList& list);
