#ifndef MEADOW_SIM_GRAPHICS_H
#define MEADOW_SIM_GRAPHICS_H

#include <ncurses.h>
#include "../Animals/Cow.h"
#include "../Animals/Rabbit.h"
#include "../Animals/Wolf.h"

class Graphics {
    std::vector<Cow*> &cows;
    std::vector<Rabbit*> &rabbits;
    std::vector<Rabbit_Hole*> &rabbit_holes;
    std::vector<Wolf*> &wolves;
    Meadow &meadow;
    Sun &sun;

    int max_x, max_y; // TODO

    void define_colors();
    void draw_sun(WINDOW *window);
    void update_sun(WINDOW *window, int &prev_progress, int &progress_index);
    void draw_results();
    void update_cows(WINDOW *window);
    void update_rabbits(WINDOW *window);
    void update_wolves(WINDOW *window);
public:
//    std::mutex cows_mutex;
//    std::mutex rabbits_mutex;
//    std::mutex rabbit_holes_mutex;
//    std::mutex wolves_mutex;

    Graphics(std::vector<Cow*> &cows, std::vector<Rabbit*> &rabbits, std::vector<Rabbit_Hole*> &rabbitHoles,
             std::vector<Wolf*> &wolves, Meadow &meadow, Sun &sun);

    void init();

    void update_progress_bar(WINDOW *window, int &prev_progress, int &progress_index, int progress, int x, int y);
};


#endif //MEADOW_SIM_GRAPHICS_H
