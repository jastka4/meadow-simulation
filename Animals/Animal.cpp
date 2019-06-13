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

    thread_local std::uniform_int_distribution<> wait(2, 4);
    thread_local std::uniform_int_distribution<> dist(0, topics.size() - 1);

    if (alive){
        status = "thinking";
        Utils::thread_safe_cout(who + " " + std::to_string(id) + " started thinking about " + topics[dist(random_generator)]);
        for (int time = wait(random_generator); time > 0 ; --time) {
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
    }

}

void Animal::drink(const std::string who) {
    meadow.pond->request(id);

    std::lock_guard<std::mutex> lock(meadow.pond->mutex);
    std::this_thread::sleep_for(std::chrono::milliseconds(250));

    thread_local std::uniform_int_distribution<> wait(2, 4);

    if (alive) {
        status = "drinking";
        Utils::thread_safe_cout(who + " " + std::to_string(id) + " is drinking water");
        for (int time = wait(random_generator); time > 0 ; --time) {
            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }

    meadow.pond->done_drinking(id);
}

const std::atomic<int> &Animal::getId() const {
    return id;
}

const std::atomic<bool> &Animal::isAlive() const {
    return alive;
}

const std::string &Animal::getStatus() const {
    return status;
}
