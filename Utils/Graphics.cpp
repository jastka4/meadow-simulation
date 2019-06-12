#include "Graphics.h"
#include <ncurses.h>

constexpr int COLOR_PINK = 8;

void Graphics::init() {
    initscr();        //ncurses start
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();        //pressed characters do not print on the screen
    cbreak();        //pressed keys are immediately returned by getch() instead of waiting until new line is read

    define_colors();

    draw_sun();
    draw_table();
}

void Graphics::draw_table() {
    mvprintw(13, 35, "-------------------------------------------------------------------------------------------------------------------------");
    for (int i = 0; i < 20; ++i) {
        mvprintw(14 + i, 35, "|");
        mvprintw(14 + i, 75, "|");
        mvprintw(14 + i, 115, "|");
        mvprintw(14 + i, 155, "|");
    }
    mvprintw(14, 51, "RABBITS");
    mvprintw(14, 93, "COWS");
    mvprintw(14, 132, "WOLVES");
    mvprintw(15, 35, "-------------------------------------------------------------------------------------------------------------------------");
}

void Graphics::draw_sun() {
    mvprintw(2, 94, "SUN");

    attron(COLOR_PAIR(2));
    mvprintw(3,  80, "           |");
    mvprintw(4,  80, "     \\     |     /");
    mvprintw(5, 80, "       \\       /");
    mvprintw(6, 80, "         ,d8b,");
    mvprintw(7, 90, "88888 ---");
    mvprintw(8, 91, "8P'");
    mvprintw(9, 95, "\\");
    mvprintw(10, 80, "           |     \\");
    mvprintw(11, 80, "           |");
    attroff(COLOR_PAIR(2));

    attron(COLOR_PAIR(6));
    mvprintw(7, 80, " (')-\")_");
    mvprintw(8, 80, "('-  (. ')9'");
    mvprintw(9, 80, " '-.(PjP)'");

    mvprintw(5, 105, ".,");
    mvprintw(6, 102, ";';'  ';'.");
    mvprintw(7, 100, "';.,;    ,;");
    mvprintw(8, 104, "'.';.'");
    attroff(COLOR_PAIR(6));
}

//void Graphics::redraw_fork(const int color, const int x, const int y) {
////    attron(COLOR_PAIR(color));
////    mvprintw(x, y, "--<=");
////    attroff(COLOR_PAIR(color));
////}

void Graphics::define_colors() {
    start_color();
    init_color(COLOR_PINK, 800, 410, 790); // new pink color

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_PINK, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
}
