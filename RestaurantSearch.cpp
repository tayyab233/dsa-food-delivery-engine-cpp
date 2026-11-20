#include "RestaurantSearch.h"

void RestaurantSearch::addLocalChef(int id, const string& name, const string& area) {
    unsortedLocalChefs.push_back({id, name, area});
}

void RestaurantSearch::addTopTier(int id, const string& name, const string& area) {
    sortedTopTier.push_back({id, name, area});
    sort(sortedTopTier.begin(), sortedTopTier.end(),
         [](const Restaurant& a, const Restaurant& b){ return a.id < b.id; });
}

int RestaurantSearch::linearSearch(int id, string& outName) const {
    for (size_t i = 0; i < unsortedLocalChefs.size(); ++i) {
        if (unsortedLocalChefs[i].id == id) {
            outName = unsortedLocalChefs[i].name;
            return (int)i;
        }
    }
    return -1;
}

int RestaurantSearch::binarySearch(int id, string& outName) const {
    int lo = 0, hi = (int)sortedTopTier.size() - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (sortedTopTier[mid].id == id) {
            outName = sortedTopTier[mid].name;
            return mid;
        } else if (sortedTopTier[mid].id < id) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}