#ifndef MEADOW_SIM_UTILS_H
#define MEADOW_SIM_UTILS_H


#include <mutex>
#include <iostream>

class Utils {
    static std::mutex mutex;
public:
    static void threadSafeCout(const std::string& text);
};


#endif //MEADOW_SIM_UTILS_H
