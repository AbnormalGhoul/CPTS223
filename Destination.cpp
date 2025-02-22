#include "Destination.h"

Destination::Destination(int pos, std::string cityName) : position(pos), name(cityName) {}
Destination::~Destination() {}
void Destination::printPosition() const { std::cout << position << std::endl; }
void Destination::printDestinationName() const { std::cout << name << std::endl; }
std::string Destination::getName() const { return name; }