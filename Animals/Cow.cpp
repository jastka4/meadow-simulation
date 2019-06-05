#include <array>
#include "Cow.h"

Cow::Cow(int id, Grass &grass, Meadow &meadow, Pond &pond) : Animal(id, meadow), grass(grass), pond(pond) {}

void Cow::live() {
    meadow.synchronization.wait();

    do {
        eat();
        drink();
        think();
    } while (meadow.ready);
}

void Cow::eat() {
    grass.request(id);

    std::lock_guard<std::mutex> lock(grass.mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);

    std::cout << id << " is eating grass" << std::endl;
    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    grass.done_eating();
}

void Cow::drink() {
    pond.request(id);

    std::lock_guard<std::mutex> lock(pond.mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);

    std::cout << id << " is eating grass" << std::endl;
    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }

    pond.done_drinking(id);
}

void Cow::think() {
    static constexpr std::array<const char *, 5> topics {{
        "politics", "art", "the meaning of life", "the source of morality", "how many straws makes a bale"
    }};

    thread_local std::uniform_int_distribution<> wait(2, 4);
    thread_local std::uniform_int_distribution<> dist(0, topics.size() - 1);

    std::cout << id << " started thinking about " << topics[dist(random_generator)] << std::endl;

    for (int time = wait(random_generator); time > 0 ; --time) {
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
}
