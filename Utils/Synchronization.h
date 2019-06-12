#ifndef MEADOW_SIM_SYNCHRONIZATION_H
#define MEADOW_SIM_SYNCHRONIZATION_H


#include <mutex>

struct Synchronization {
    std::mutex mutex;
    std::condition_variable condition_variable;

public:
    void wait();
    void notify_all();
};


#endif //MEADOW_SIM_SYNCHRONIZATION_H
