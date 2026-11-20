#include "NavigationList.h"

NavigationList::~NavigationList() {
    StopNode* cur = head;
    while (cur) { StopNode* n = cur->next; delete cur; cur = n; }
}

void NavigationList::addStop(int id, const string& addr) {
    StopNode* node = new StopNode(id, addr);
    if (!head) { head = tail = node; }
    else { node->prev = tail; tail->next = node; tail = node; }
}

void NavigationList::startRoute() { current = head; showCurrent(); }

void NavigationList::nextStop() {
    if (!current) { cout << "  Start route first.\n"; return; }
    if (!current->next) { cout << "  Already at last stop.\n"; return; }
    current = current->next; showCurrent();
}

void NavigationList::previousStop() {
    if (!current) { cout << "  Start route first.\n"; return; }
    if (!current->prev) { cout << "  Already at first stop.\n"; return; }
    current = current->prev; showCurrent();
}

void NavigationList::showCurrent() const {
    if (!current) { cout << "  No current stop.\n"; return; }
    cout << "  >> Current Stop: #" << current->stopID
         << " @ " << current->address << "\n";
}

void NavigationList::showAll() const {
    cout << "\n[Multi-Drop Route]\n";
    StopNode* cur = head;
    while (cur) {
        cout << (cur == current ? "  * " : "    ")
             << "#" << cur->stopID << " @ " << cur->address << "\n";
        cur = cur->next;
    }
}