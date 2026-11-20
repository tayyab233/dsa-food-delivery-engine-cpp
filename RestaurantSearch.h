#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Restaurant {
    int id;
    string name;
    string area;
};

class RestaurantSearch {
private:
    vector<Restaurant> unsortedLocalChefs;  // dynamic home-chefs
    vector<Restaurant> sortedTopTier;       // sorted by ID

public:
    void addLocalChef(int id, const string& name, const string& area);
    void addTopTier(int id, const string& name, const string& area); // keeps sorted
    int  linearSearch(int id, string& outName) const;
    int  binarySearch(int id, string& outName) const;
};