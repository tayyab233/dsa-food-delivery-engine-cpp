#pragma once
#include <iostream>
#include <string>
using namespace std;

class RiderArray {
private:
    static const int CAPACITY = 100;
    int riderIDs[CAPACITY];
    bool occupied[CAPACITY];   // tracks active slots
    int count;

public:
    RiderArray();
    bool insertAt(int index, int riderID);   // add rider at specific slot
    bool removeRider(int riderID);           // nullify slot safely
    void traverse() const;                   // broadcast simulation
    int  getActiveCount() const { return count; }
};