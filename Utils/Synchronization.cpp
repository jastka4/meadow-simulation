#include "Synchronization.h"

void Synchronization::wait() {
    /* Condition_variable unlocks its mutex when going to sleep upon calls to wait. That is why a lock_guard is not sufficient here. */
    std::unique_lock<std::mutex> lock(mutex);
    while (sleep) {
        condition_variable.wait(lock);
    }
}

void Synchronization::notify_all() {
    std::unique_lock<std::mutex> lock(mutex);
    condition_variable.notify_all();
}

void Synchronization::notify_one() {
    std::unique_lock<std::mutex> lock(mutex);
    condition_variable.notify_one();
}

const std::atomic_bool &Synchronization::getSleep() const {
    return sleep;
}

void Synchronization::setSleep(const bool sleep) {
    this->sleep = sleep;
}
