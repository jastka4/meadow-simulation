#include "Rabbit_Hole.h"

Rabbit_Hole::Rabbit_Hole(int capacity) : capacity(capacity) {}

void Rabbit_Hole::request(int id) {
    if (rabbits.size() < capacity) {
        std::lock_guard<std::mutex> lock(mutex);
        rabbits.push_back(id);
        Utils::thread_safe_cout("Rabbit " + std::to_string(id) + " started hiding");
    } else {
        synchronization.wait();
    }
}

void Rabbit_Hole::done_hiding(int id) {
    rabbits.erase(std::remove(rabbits.begin(), rabbits.end(), id), rabbits.end());
    synchronization.notify_all();
}

int Rabbit_Hole::get_capacity() const {
    return capacity;
}

int Rabbit_Hole::get_number_of_animals() {
    return rabbits.size();
}
