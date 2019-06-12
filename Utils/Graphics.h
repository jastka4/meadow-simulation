#ifndef MEADOW_SIM_GRAPHICS_H
#define MEADOW_SIM_GRAPHICS_H

#include <ncurses.h>

class Graphics {
    void draw_table();
public:
    void init();
    void define_colors();
    void draw_sun();
};


#endif //MEADOW_SIM_GRAPHICS_H
