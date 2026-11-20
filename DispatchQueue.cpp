#include "DispatchQueue.h"

DispatchQueue::~DispatchQueue() {
    if (!tail) return;
    RiderNode* cur = tail->next;
    tail->next = nullptr;
    while (cur) { RiderNode* n = cur->next; delete cur; cur = n; }
}

void DispatchQueue::enqueue(int riderID) {
    RiderNode* node = new RiderNode(riderID);
    if (!tail) { tail = node; node->next = node; }
    else { node->next = tail->next; tail->next = node; tail = node; }
    ++size;
}

int DispatchQueue::assignNext() {
    if (!tail) return -1;
    RiderNode* front = tail->next;
    int id = front->riderID;
    if (front == tail) { delete front; tail = nullptr; }
    else { tail->next = front->next; delete front; }
    --size;
    return id;
}

void DispatchQueue::display() const {
    cout << "\n[Round-Robin Dispatch Queue] (size=" << size << ")\n";
    if (!tail) { cout << "  (empty)\n"; return; }
    RiderNode* cur = tail->next;
    do {
        cout << "  Rider " << cur->riderID << "\n";
        cur = cur->next;
    } while (cur != tail->next);
}