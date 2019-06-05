#include <utility>
#include "Animal.h"

Animal::Animal(int id, Meadow &meadow) : id(id), meadow(meadow), live_thread(&Animal::live, this) {}

Animal::~Animal() {
    live_thread.join();
}

int Animal::getId() const {
    return id;
}

