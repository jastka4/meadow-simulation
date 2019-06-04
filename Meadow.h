#ifndef MEADOW_SIM_MEADOW_H
#define MEADOW_SIM_MEADOW_H

#include <atomic>
#include <thread>

struct Synchronization {
    std::mutex mutex;
    std::condition_variable condition_variable;

public:
    void wait() {
        std::unique_lock<std::mutex> lock(mutex);
        condition_variable.wait(lock);
    }

    void notify_all() {
        std::unique_lock<std::mutex> lock(mutex);
        condition_variable.notify_all();
    }
};

struct Meadow {
    std::atomic<bool> ready{false};
    Synchronization synchronization;
};


#endif //MEADOW_SIM_MEADOW_H
