#ifndef MEADOW_SIM_POND_H
#define MEADOW_SIM_POND_H


#include <algorithm>
#include <vector>
#include "../Utils/Synchronization.h"

class Pond {
    std::vector<int> animals;
    Synchronization synchronization;
    std::atomic_int capacity;

public:
    std::mutex mutex;

    explicit Pond(int capacity);

    void request(int id);
    void done_drinking(int id);
    int get_capacity() const;
    int get_number_of_animals();
};


#endif //MEADOW_SIM_POND_H
