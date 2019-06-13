#include "Graphics.h"
#include <ncurses.h>

constexpr int COLOR_PINK = 8;

Graphics::Graphics(std::vector<Cow *> &cows, std::vector<Rabbit *> &rabbits, std::vector<Rabbit_Hole *> &rabbitHoles,
                   std::vector<Wolf *> &wolves, Meadow &meadow, Sun &sun)
        : cows(cows), rabbits(rabbits), rabbit_holes(rabbitHoles), wolves(wolves), meadow(meadow), sun(sun) {}

void Graphics::init() {
    initscr();        //ncurses start
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();        //pressed characters do not print on the screen
    cbreak();        //pressed keys are immediately returned by getch() instead of waiting until new line is read

    getmaxyx(stdscr, max_y, max_x);
    define_colors();

    draw_sun(); // TODO - draw it in a window
    draw_results();
}

void Graphics::update_cows(WINDOW *window) {
    for (int i = 0; i < cows.size(); ++i) {
        Cow* cow = cows.at(i);
//        std::string str = std::to_string(cow->isAlive());
        //cow mutex
        std::string state = cow->getStatus();
        const char *cstr = state.c_str();
        mvwprintw(window, 4 + i, 2, cstr);
    }
    wrefresh(window);
}

void Graphics::update_rabbits(WINDOW *window) {
    for (int i = 0; i < rabbits.size(); ++i) {
        Rabbit *rabbit = rabbits.at(i);
        std::string str = std::to_string(rabbit->isAlive());
        // rabbit mutex
        std::string state = rabbit->getStatus() + " " + str;
        const char *cstr = state.c_str();
        mvwprintw(window, 4 + i, 2, cstr);
    }
    wrefresh(window);

}

void Graphics::update_wolves(WINDOW *window) {
    for (int i = 0; i < wolves.size(); ++i) {
        Wolf *wolf = wolves.at(i);
        // wolf mutex
        std::string state = wolf->getStatus();
        const char *cstr = state.c_str();
        mvwprintw(window, 4 + i, 2, cstr);
    }
    wrefresh(window);
}

void Graphics::draw_results() {
    WINDOW *rabbits_window = newwin(40, (max_x - 70) / 3, 13, 35 + (max_x - 70) / 3);
    mvwhline(rabbits_window, 3, 0, ACS_HLINE, (max_x - 70) / 3);
    box(rabbits_window, 0, 0);
    wrefresh(rabbits_window);

    WINDOW *cows_window = newwin(40, (max_x - 70) / 3, 13, 35);
    mvwhline(cows_window, 3, 0, ACS_HLINE, (max_x - 70) / 3);
    box(cows_window, 0, 0);
    wrefresh(cows_window);

    WINDOW *wolves_window = newwin(40, (max_x - 70) / 3, 13, 35 + (max_x - 70) / 3 * 2);
    mvwhline(wolves_window, 3, 0, ACS_HLINE, (max_x - 70) / 3);
    box(wolves_window, 0, 0);
    wrefresh(wolves_window);

    int sun_progress_index = 0;
    int sun_prev_progress = 0;

    do {
        update_rabbits(rabbits_window);
        update_cows(cows_window);
        update_wolves(wolves_window);

        update_sun(sun_prev_progress, sun_progress_index);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (meadow.ready);

}

void Graphics::update_sun(int &prev_progress, int &progress_index) {
    //mutex ?
    bool is_day = sun.getIsDay();

    int progress = sun.getProgress();
    const char *cprogress = (std::to_string(progress) + " %").c_str();

    std::string state = is_day ? "DAY  " : "NIGHT";
    const char *cstate = state.c_str();

    progress = Utils::round_up(progress);

    if (progress <= 100) {
        if (prev_progress != progress) {
            mvaddch(2, 94 + progress_index , '#');
            progress_index++;
            prev_progress = progress;
        }
    }
    if (progress_index > 10) {
        move(2, 94);
        clrtoeol();
        progress_index = 0;
        prev_progress = 0;
    }

    mvprintw(1, 94, cstate);
    mvprintw(2, 93, "[");
    mvprintw(2, 104, "]");
    mvprintw(2, 107, cprogress);

    refresh();
}

void Graphics::draw_sun() {
    attron(COLOR_PAIR(2));
    mvprintw(3, 80, "           |");
    mvprintw(4, 80, "     \\     |     /");
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

    refresh();
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
