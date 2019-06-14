#ifndef MEADOW_SIM_SYNCHRONIZATION_H
#define MEADOW_SIM_SYNCHRONIZATION_H


#include <mutex>

struct Synchronization {
    std::mutex mutex;
    std::condition_variable condition_variable;
    std::atomic_bool sleep;

public:
    void wait();
    void notify_all();
    void notify_one();

    const std::atomic_bool &getSleep() const;
    void setSleep(bool sleep);
};


#endif //MEADOW_SIM_SYNCHRONIZATION_H
