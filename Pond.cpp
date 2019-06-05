#include <iostream>
#include "Pond.h"

Pond::Pond(int capacity) : capacity(capacity) {}

void Pond::request(int id) {
    if (animals.size() < capacity) {
        std::lock_guard<std::mutex> lock(mutex);
        animals.push_back(id);
        std::cout << id << " started drinking" << std::endl;
    } else {
        synchronization.wait();
    }
}

void Pond::done_drinking(int id) {
    animals.erase(std::remove(animals.begin(), animals.end(), id), animals.end());
    synchronization.notify_all();
}
