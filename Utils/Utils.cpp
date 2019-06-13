#include "Utils.h"

std::mutex Utils::mutex;

void Utils::thread_safe_cout(const std::string &text) {
//    std::lock_guard<std::mutex> lock(mutex);
//    std::cout << text << std::endl;
}

int Utils::round_up(int to_round) {
    if (to_round % 10 == 0) {
        return to_round;
    }
    return (10 - to_round % 10) + to_round;
}

int Utils::get_percentage(int numerator, int denominator) {
    return (int) (((float) numerator / (float) denominator) * 100);
}
