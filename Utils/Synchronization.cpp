#include "Synchronization.h"

void Synchronization::wait() {
    /* Condition_variable unlocks its mutex when going to sleep upon calls to wait. That is why a lock_guard is not sufficient here. */
    std::unique_lock<std::mutex> lock(mutex);
    condition_variable.wait(lock);
}

void Synchronization::notify_all() {
    std::unique_lock<std::mutex> lock(mutex);
    condition_variable.notify_all();
}
