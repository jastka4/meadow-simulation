#include "Animal.h"

Animal::Animal(int id, Meadow &meadow) : id(id), meadow(meadow), live_thread(&Animal::live, this), alive(true), status("waiting ") {}

Animal::~Animal() {
    if (live_thread.joinable()) {
        live_thread.join();
    }
}

void Animal::think(const std::string who) {
    static constexpr std::array<const char *, 5> topics {{
         "politics", "art", "the meaning of life", "the source of morality", "how many straws makes a bale"
    }};

    thread_local std::uniform_int_distribution<> wait(10, 14);
    thread_local std::uniform_int_distribution<> dist(0, topics.size() - 1);

    if (alive){
        status = "thinking";
        Utils::thread_safe_cout(who + " " + std::to_string(id) + " started thinking about " + topics[dist(random_generator)]);
        int time = wait(random_generator);
        for (int i = time, counter = 0; i > 0; --i) {
            progress = Utils::get_percentage(counter, time);
            counter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        progress = 0;
    }

}

void Animal::drink(const std::string who) {
//    std::lock_guard<std::mutex> lock(meadow.pond->mutex);
    meadow.pond->request(id);

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
    thread_local std::uniform_int_distribution<> wait(10, 14);

    if (alive) {
        status = "drinking";
        Utils::thread_safe_cout(who + " " + std::to_string(id) + " is drinking water");
        int time = wait(random_generator);
        for (int i = time, counter = 0; i > 0; --i) {
            progress = Utils::get_percentage(counter, time);
            counter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        progress = 0;
    }

    meadow.pond->done_drinking(id);
}

const std::atomic_int &Animal::getId() const {
    return id;
}

const std::atomic<bool> &Animal::isAlive() const {
    return alive;
}

const std::string &Animal::getStatus() const {
    return status;
}

const std::atomic_int &Animal::getProgress() const {
    return progress;
}
