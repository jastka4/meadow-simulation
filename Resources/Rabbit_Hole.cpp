#include "Rabbit_Hole.h"

Rabbit_Hole::Rabbit_Hole(int capacity) : capacity(capacity) {}

void Rabbit_Hole::request(int id) {
    std::lock_guard<std::mutex> lock(mutex);
    if (rabbits.size() < capacity) {
        rabbits.push_back(id);
        Utils::thread_safe_cout("Rabbit " + std::to_string(id) + " started hiding");
    } else {
        synchronization.setSleep(true);
        synchronization.wait();
    }
}

void Rabbit_Hole::done_hiding(int id) {
    {
        std::lock_guard<std::mutex> lock(mutex);
        rabbits.erase(std::remove(rabbits.begin(), rabbits.end(), id), rabbits.end());
    }
    synchronization.setSleep(false);
    synchronization.notify_all();
}

int Rabbit_Hole::get_capacity() const {
    return capacity;
}

int Rabbit_Hole::get_number_of_animals() {
    return rabbits.size();
}
