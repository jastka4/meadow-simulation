#include "Utils.h"

std::mutex Utils::mutex;

void Utils::threadSafeCout(const std::string &text) {
//    std::lock_guard<std::mutex> lock(mutex);
//    std::cout << text << std::endl;
}
