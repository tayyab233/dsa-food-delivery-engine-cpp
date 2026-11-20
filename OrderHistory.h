#pragma once
#include <iostream>
#include <string>
using namespace std;

struct OrderNode {
    int orderID;
    string restaurantName;
    double billAmount;
    OrderNode* next;
    OrderNode(int id, string r, double b)
        : orderID(id), restaurantName(r), billAmount(b), next(nullptr) {}
};

class OrderHistory {
private:
    OrderNode* head;
    OrderNode* tail;
    int size;

public:
    OrderHistory() : head(nullptr), tail(nullptr), size(0) {}
    ~OrderHistory();

    void appendOrder(int id, const string& r, double bill);  // insert at end
    bool deleteOrder(int id);                                // cancel/archive
    void traverse() const;                                   // timeline feed
    int  getSize() const { return size; }
};