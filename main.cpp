#include <iostream>
#include <array>
#include "Sun.h"
#include "Animals/Animal.h"
#include "Grass.h"
#include "Animals/Cow.h"
#include "Pond.h"

int main() {
    Meadow meadow;
    Sun *sun = new Sun(meadow);
    Pond *pond = new Pond(10);

    std::array<Grass, 3> grass {{
        {1, *sun, meadow},
        {2, *sun, meadow},
        {3, *sun, meadow}
    }};

    std::array<Cow, 5> animals {{
       {1, grass[0], meadow, *pond},
       {2, grass[1], meadow, *pond},
       {3, grass[1], meadow, *pond},
       {4, grass[2], meadow, *pond},
       {5, grass[2], meadow, *pond}
    }};

    std::this_thread::sleep_for(std::chrono::seconds(1));
    meadow.ready = true;
    meadow.synchronization.notify_all();

    std::this_thread::sleep_for(std::chrono::seconds(30));
    meadow.ready = false;

    std::cout << "===== FINISHING =====" << std::endl;
    std::cout << "Animals are going on holiday!" << std::endl;

    return 0;
}