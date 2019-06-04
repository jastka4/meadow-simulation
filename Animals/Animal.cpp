#include <utility>
#include "Animal.h"

Animal::Animal(const std::string &name, Meadow &meadow) : name(name), meadow_thread(meadow), live_thread(&Animal::live, this) {}

void Animal::live() {
    meadow_thread.synchronization.wait();

//    do {
//        eat();
//        think();
//    } while (dinner_table.ready);
}

