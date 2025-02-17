#include "ListMyJosephus.h"

ListMyJosephus::ListMyJosephus(int m, int n) : M(m), N(n) {
    for (int i = 0; i < N; i++) {
        circle.emplace_back(i, "City" + std::to_string(i));
    }
}
ListMyJosephus::~ListMyJosephus() {}
void ListMyJosephus::clear() { circle.clear(); }
bool ListMyJosephus::isEmpty() const { return circle.empty(); }
int ListMyJosephus::currentSize() const { return circle.size(); }
void ListMyJosephus::eliminateDestination() {
    auto it = circle.begin();
    while (circle.size() > 1) {
        for (int i = 0; i < M - 1; i++) {
            it++;
            if (it == circle.end()) it = circle.begin();
        }
        it = circle.erase(it);
        if (it == circle.end()) it = circle.begin();
    }
}
void ListMyJosephus::printAllDestinations() const {
    for (const auto& dest : circle) {
        dest.printDestinationName();
    }
}