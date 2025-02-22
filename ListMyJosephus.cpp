#include "ListMyJosephus.h"

ListMyJosephus::ListMyJosephus(int m, int n, const std::vector<std::string>& cityNames) : M(m), N(n) {
    for (int i = 0; i < N && i < cityNames.size(); i++) {
        circle.emplace_back(i, cityNames[i]);
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
        std::cout << "Eliminating: " << it->getName() << std::endl;
        it = circle.erase(it);
        if (it == circle.end()) it = circle.begin();
    }
}

void ListMyJosephus::printAllDestinations(std::ostream& os) const {
    for (const auto& dest : circle) {
        os << dest.getName() << std::endl;
    }
}