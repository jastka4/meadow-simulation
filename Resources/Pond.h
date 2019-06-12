#ifndef MEADOW_SIM_POND_H
#define MEADOW_SIM_POND_H


#include <algorithm>
#include <vector>
#include "../Utils/Synchronization.h"

class Pond {
    std::vector<int> animals;
    Synchronization synchronization;
    int capacity;

public:
    std::mutex mutex;

    explicit Pond(int capacity);

    void request(int id);
    void done_drinking(int id);
};


#endif //MEADOW_SIM_POND_H
