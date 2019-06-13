#ifndef MEADOW_SIM_UTILS_H
#define MEADOW_SIM_UTILS_H


#include <mutex>
#include <iostream>

class Utils {
    static std::mutex mutex;
public:
    static void thread_safe_cout(const std::string& text);
    static int round_up(int to_round);
    static int get_percentage(int numerator, int denominator);
};


#endif //MEADOW_SIM_UTILS_H
