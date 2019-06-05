#include <iostream>
#include <array>
#include "Sun.h"
#include "Animals/Animal.h"
#include "Resources/Grass.h"
#include "Animals/Cow.h"
#include "Resources/Rabbit_Hole.h"
#include "Animals/Rabbit.h"
#include "Animals/Wolf.h"

int main() {
    Pond *pond = new Pond(10);
    Meadow meadow(pond);
    Sun *sun = new Sun(meadow);

    std::array<Grass, 3> grass {{
        {1, *sun, meadow},
        {2, *sun, meadow},
        {3, *sun, meadow}
    }};

    std::array<Rabbit_Hole, 4> rabbit_holes{{{3}, {3}, {3}, {3}}};

//    std::array<Cow, 3> cows {{
//       {1, grass[0], meadow},
//       {2, grass[1], meadow},
//       {3, grass[1], meadow}
//    }};

    std::array<Rabbit, 3> rabbits {{
        {1, grass[0], meadow, rabbit_holes[0]},
        {2, grass[1], meadow, rabbit_holes[0]},
        {3, grass[1], meadow, rabbit_holes[0]}
    }};

    std::array<Wolf, 3> wolfs {{
       {1, rabbits[0], meadow},
       {2, rabbits[1], meadow},
       {3, rabbits[1], meadow}
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