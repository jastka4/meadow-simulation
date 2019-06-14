#include <iostream>
#include "Pond.h"

Pond::Pond(int capacity) : capacity(capacity) {}

void Pond::request(int id) {
    if (animals.size() < capacity) {
        std::lock_guard<std::mutex> lock(mutex);
        animals.push_back(id);
    } else {
        synchronization.setSleep(true);
        synchronization.wait();
    }
}

void Pond::done_drinking(int id) {
    animals.erase(std::remove(animals.begin(), animals.end(), id), animals.end());
    synchronization.setSleep(false);
    synchronization.notify_all();
}

int Pond::get_capacity() const {
    return capacity;
}

int Pond::get_number_of_animals() {
    return animals.size();
}
