#pragma once
#include <iostream>
using namespace std;

struct RiderNode {
    int riderID;
    RiderNode* next;
    RiderNode(int id) : riderID(id), next(nullptr) {}
};

class DispatchQueue {
private:
    RiderNode* tail;   // tail->next is front (head)
    int size;

public:
    DispatchQueue() : tail(nullptr), size(0) {}
    ~DispatchQueue();

    void enqueue(int riderID);
    int  assignNext();          // round-robin pop of next rider
    void display() const;
    int  getSize() const { return size; }
};