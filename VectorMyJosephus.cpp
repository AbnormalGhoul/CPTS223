#include "VectorMyJosephus.h"

VectorMyJosephus::VectorMyJosephus(int m, int n, const std::vector<std::string>& cityNames) : M(m), N(n) {
    for (int i = 0; i < N && i < cityNames.size(); i++) {
        circle.emplace_back(i, cityNames[i]);
    }
}

VectorMyJosephus::~VectorMyJosephus() {}

void VectorMyJosephus::clear() { circle.clear(); }

bool VectorMyJosephus::isEmpty() const { return circle.empty(); }

int VectorMyJosephus::currentSize() const { return circle.size(); }

void VectorMyJosephus::eliminateDestination() {
    int index = 0;
    while (circle.size() > 1) {
        index = (index + M - 1) % circle.size();
        std::cout << "Eliminating: " << circle[index].getName() << std::endl;
        circle.erase(circle.begin() + index);
    }
}

void VectorMyJosephus::printAllDestinations(std::ostream& os) const {
    for (const auto& dest : circle) {
        os << dest.getName() << std::endl;
    }
}