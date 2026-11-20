#include <iostream>
#include <string>
#include <limits>
#include "RiderArray.h"
#include "RestaurantSearch.h"
#include "OrderHistory.h"
#include "NavigationList.h"
#include "DispatchQueue.h"
#include "SurgeEvaluator.h"
using namespace std;

static int readInt(const string& prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) { cin.ignore(numeric_limits<streamsize>::max(), '\n'); return x; }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input.\n";
    }
}

static double readDouble(const string& prompt) {
    double x;
    while (true) {
        cout << prompt;
        if (cin >> x) { cin.ignore(numeric_limits<streamsize>::max(), '\n'); return x; }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input.\n";
    }
}

static string readLine(const string& prompt) {
    cout << prompt;
    string s;
    getline(cin, s);
    return s;
}

// ------------------- Module 1 Menu -------------------
void riderArrayMenu() {
    RiderArray arr;
    // seed some riders
    arr.insertAt(0, 101); arr.insertAt(1, 102); arr.insertAt(2, 103);

    while (true) {
        cout << "\n--- Active Rider Queue (Array) ---\n"
             << "1. Traverse (broadcast)\n"
             << "2. Insert rider at index\n"
             << "3. Remove rider (nullify)\n"
             << "0. Back\n";
        int c = readInt("Choice: ");
        if (c == 0) break;
        if (c == 1) arr.traverse();
        else if (c == 2) {
            int idx = readInt("Index: ");
            int id  = readInt("Rider ID: ");
            cout << (arr.insertAt(idx, id) ? "  Inserted.\n" : "  Failed.\n");
        } else if (c == 3) {
            int id = readInt("Rider ID: ");
            cout << (arr.removeRider(id) ? "  Removed.\n" : "  Not found.\n");
        }
    }
}

// ------------------- Module 2 Menu -------------------
void restaurantSearchMenu() {
    RestaurantSearch rs;
    // local chefs (unsorted)
    rs.addLocalChef(501, "Biryani Bites", "Johar Town");
    rs.addLocalChef(503, "Chacha Tikka", "Model Town");
    rs.addLocalChef(502, "Home Karahi", "Gulberg");
    // top-tier (kept sorted)
    rs.addTopTier(1001, "Pizza Hut", "DHA");
    rs.addTopTier(1003, "KFC", "Gulberg");
    rs.addTopTier(1002, "Hardee's", "MM Alam");

    while (true) {
        cout << "\n--- Restaurant Lookup ---\n"
             << "1. Linear search (local chefs)\n"
             << "2. Binary search (top-tier)\n"
             << "0. Back\n";
        int c = readInt("Choice: ");
        if (c == 0) break;
        int id = readInt("Restaurant ID: ");
        string name;
        int idx = -1;
        if (c == 1) idx = rs.linearSearch(id, name);
        else if (c == 2) idx = rs.binarySearch(id, name);
        if (idx >= 0) cout << "  Found: " << name << " (index " << idx << ")\n";
        else cout << "  Not found.\n";
    }
}

// ------------------- Module 3 Menu -------------------
void orderHistoryMenu() {
    OrderHistory oh;
    while (true) {
        cout << "\n--- Customer Order History (SLL) ---\n"
             << "1. Append order\n"
             << "2. Delete order (cancel/archive)\n"
             << "3. Traverse timeline\n"
             << "0. Back\n";
        int c = readInt("Choice: ");
        if (c == 0) break;
        if (c == 1) {
            int id = readInt("Order ID: ");
            string r = readLine("Restaurant: ");
            double b = readDouble("Bill: ");
            oh.appendOrder(id, r, b);
        } else if (c == 2) {
            int id = readInt("Order ID to delete: ");
            cout << (oh.deleteOrder(id) ? "  Deleted.\n" : "  Not found.\n");
        } else if (c == 3) oh.traverse();
    }
}

// ------------------- Module 4a Menu -------------------
void navigationMenu() {
    NavigationList nav;
    nav.addStop(1, "Liberty Market");
    nav.addStop(2, "Gulberg Main Blvd");
    nav.addStop(3, "DHA Phase 5");
    nav.addStop(4, "Johar Town Block G");
    nav.startRoute();

    while (true) {
        cout << "\n--- Rider Navigation (DLL) ---\n"
             << "1. Next stop\n"
             << "2. Previous stop\n"
             << "3. Show all stops\n"
             << "4. Restart route\n"
             << "0. Back\n";
        int c = readInt("Choice: ");
        if (c == 0) break;
        if (c == 1) nav.nextStop();
        else if (c == 2) nav.previousStop();
        else if (c == 3) nav.showAll();
        else if (c == 4) nav.startRoute();
    }
}

// ------------------- Module 4b Menu -------------------
void dispatchQueueMenu() {
    DispatchQueue dq;
    dq.enqueue(201); dq.enqueue(202); dq.enqueue(203);

    while (true) {
        cout << "\n--- Round-Robin Dispatch (CLL) ---\n"
             << "1. Enqueue rider\n"
             << "2. Assign next rider (pop front)\n"
             << "3. Display queue\n"
             << "0. Back\n";
        int c = readInt("Choice: ");
        if (c == 0) break;
        if (c == 1) { int id = readInt("Rider ID: "); dq.enqueue(id); }
        else if (c == 2) {
            int id = dq.assignNext();
            if (id < 0) cout << "  Queue empty.\n";
            else cout << "  Assigned Rider " << id << " to next batch.\n";
        } else if (c == 3) dq.display();
    }
}

// ------------------- Module 5 Menu -------------------
void surgeEvaluatorMenu() {
    SurgeEvaluator se;
    cout << "\n--- Surge / Promo Evaluator (Stack) ---\n";
    cout << "Example expression: 500 * 1.5 + 50 - 30\n";
    string expr = readLine("Enter infix expression: ");
    try {
        string post = se.infixToPostfix(expr);
        cout << "  Postfix: " << post << "\n";
        double val = se.evaluatePostfix(post);
        cout << "  Final payable amount: Rs. " << val << "\n";
    } catch (const exception& e) {
        cout << "  Error: " << e.what() << "\n";
    }
}

// ------------------- Main -------------------
int main() {
    cout << "=====================================================\n"
         << " Food Delivery Dispatch & Tracking Engine (Lahore)   \n"
         << "=====================================================\n";
    while (true) {
        cout << "\n===== MAIN MENU =====\n"
             << "1. Active Rider Queue (Array)\n"
             << "2. Restaurant Lookup (Linear/Binary Search)\n"
             << "3. Customer Order History (Singly Linked List)\n"
             << "4. Rider Navigation (Doubly Linked List)\n"
             << "5. Round-Robin Dispatch (Circular Linked List)\n"
             << "6. Surge Pricing / Promo Evaluator (Stack)\n"
             << "0. Exit\n";
        int c = readInt("Choice: ");
        switch (c) {
            case 1: riderArrayMenu(); break;
            case 2: restaurantSearchMenu(); break;
            case 3: orderHistoryMenu(); break;
            case 4: navigationMenu(); break;
            case 5: dispatchQueueMenu(); break;
            case 6: surgeEvaluatorMenu(); break;
            case 0: cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}