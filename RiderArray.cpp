#include "RiderArray.h"

RiderArray::RiderArray() : count(0) {
    for (int i = 0; i < CAPACITY; ++i) occupied[i] = false;
}

bool RiderArray::insertAt(int index, int riderID) {
    if (index < 0 || index >= CAPACITY) return false;
    if (occupied[index]) {
        // find next free slot from index
        int i = index;
        while (i < CAPACITY && occupied[i]) ++i;
        if (i == CAPACITY) return false;
        index = i;
    }
    riderIDs[index] = riderID;
    occupied[index] = true;
    ++count;
    return true;
}

bool RiderArray::removeRider(int riderID) {
    for (int i = 0; i < CAPACITY; ++i) {
        if (occupied[i] && riderIDs[i] == riderID) {
            occupied[i] = false;   // nullify without shifting
            --count;
            return true;
        }
    }
    return false;
}

void RiderArray::traverse() const {
    cout << "\n[Active Riders] (count=" << count << ")\n";
    for (int i = 0; i < CAPACITY; ++i) {
        if (occupied[i])
            cout << "  Slot " << i << " -> Rider " << riderIDs[i] << "\n";
    }
    if (count == 0) cout << "  (none online)\n";
}