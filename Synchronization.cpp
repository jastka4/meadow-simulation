#include "Synchronization.h"

void Synchronization::wait() {
    std::unique_lock<std::mutex> lock(mutex);
    condition_variable.wait(lock);
}

void Synchronization::notify_all() {
    std::unique_lock<std::mutex> lock(mutex);
    condition_variable.notify_all();
}
