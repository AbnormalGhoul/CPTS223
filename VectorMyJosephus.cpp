#include "VectorMyJosephus.h"

VectorMyJosephus::VectorMyJosephus(int m, int n) : M(m), N(n) {
    for (int i = 0; i < N; i++) {
        circle.emplace_back(i, "City" + std::to_string(i));
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
        circle.erase(circle.begin() + index);
    }
}
void VectorMyJosephus::printAllDestinations() const {
    for (const auto& dest : circle) {
        dest.printDestinationName();
    }
}