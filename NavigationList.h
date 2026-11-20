#pragma once
#include <iostream>
#include <string>
using namespace std;

struct StopNode {
    int stopID;
    string address;
    StopNode* prev;
    StopNode* next;
    StopNode(int id, string a) : stopID(id), address(a), prev(nullptr), next(nullptr) {}
};

class NavigationList {
private:
    StopNode* head;
    StopNode* tail;
    StopNode* current;   // rider's current position

public:
    NavigationList() : head(nullptr), tail(nullptr), current(nullptr) {}
    ~NavigationList();

    void addStop(int id, const string& addr);   // append at end
    void startRoute();                          // set current to head
    void nextStop();
    void previousStop();
    void showCurrent() const;
    void showAll() const;
};