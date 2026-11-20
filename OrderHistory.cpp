#include "OrderHistory.h"

OrderHistory::~OrderHistory() {
    OrderNode* cur = head;
    while (cur) { OrderNode* nxt = cur->next; delete cur; cur = nxt; }
}

void OrderHistory::appendOrder(int id, const string& r, double bill) {
    OrderNode* node = new OrderNode(id, r, bill);
    if (!head) { head = tail = node; }
    else { tail->next = node; tail = node; }
    ++size;
    cout << "  Order #" << id << " appended to history.\n";
}

bool OrderHistory::deleteOrder(int id) {
    if (!head) return false;
    if (head->orderID == id) {
        OrderNode* del = head;
        head = head->next;
        if (!head) tail = nullptr;
        delete del; --size;
        return true;
    }
    OrderNode* cur = head;
    while (cur->next && cur->next->orderID != id) cur = cur->next;
    if (!cur->next) return false;
    OrderNode* del = cur->next;
    cur->next = del->next;
    if (del == tail) tail = cur;
    delete del; --size;
    return true;
}

void OrderHistory::traverse() const {
    cout << "\n[Order Timeline Feed] (size=" << size << ")\n";
    OrderNode* cur = head;
    int i = 1;
    while (cur) {
        cout << "  " << i++ << ". Order #" << cur->orderID
             << " | " << cur->restaurantName
             << " | Rs. " << cur->billAmount << "\n";
        cur = cur->next;
    }
    if (!head) cout << "  (no orders yet)\n";
}