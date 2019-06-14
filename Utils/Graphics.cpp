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
    draw_results();
}

void Graphics::update_cows(WINDOW *window, std::vector<int> &cows_progress_index, std::vector<int> &cows_prev_progress) {
    int x = 20;
    int y = 4;

    for (int i = 0; i < cows.size(); ++i) {
        Cow* cow = cows.at(i);

        //cow mutex
        int progress = cow->getProgress();
        update_progress_bar(window, cows_prev_progress.at(i), cows_progress_index.at(i), progress, x, y + i);

        const std::string& state = cow->getStatus();
        const char *c_str = state.c_str();
        mvwprintw(window, 4 + i, 2, c_str);
    }
    box(window, 0, 0);
    wrefresh(window);
}

void Graphics::update_rabbits(WINDOW *window, std::vector<int> &rabbits_progress_index, std::vector<int> &rabbits_prev_progress) {
    int x = 20;
    int y = 4;

    for (int i = 0; i < rabbits.size(); ++i) {
        Rabbit *rabbit = rabbits.at(i);

        int progress = 0;

        const std::string& state = rabbit->getStatus();
        const char *c_str = state.c_str();
        if (state.find("eaten") != std::string::npos) {
            wattron(window, COLOR_PAIR(4));
            mvwprintw(window, y + i, 2, c_str);
            wattroff(window, COLOR_PAIR(4));
            mvwprintw(window, y + i, x, "          ");
        } else {
            // rabbit mutex
            progress = rabbit->getProgress();
            mvwprintw(window, y + i, 2, c_str);
        }

        update_progress_bar(window, rabbits_prev_progress.at(i), rabbits_progress_index.at(i), progress, x, y + i);

    }
    box(window, 0, 0);
    wrefresh(window);

}

void Graphics::update_wolves(WINDOW *window, std::vector<int> &wolves_progress_index, std::vector<int> &wolves_prev_progress) {
    int x = 20;
    int y = 4;

    for (int i = 0; i < wolves.size(); ++i) {
        Wolf *wolf = wolves.at(i);

        // wolf mutex
        int progress = wolf->getProgress();
        update_progress_bar(window, wolves_prev_progress.at(i), wolves_progress_index.at(i), progress, x, y + i);

        // wolf mutex
        const std::string& state = wolf->getStatus();
        const char *c_str = state.c_str();
        mvwprintw(window, 4 + i, 2, c_str);
    }
    box(window, 0, 0);
    wrefresh(window);
}

void Graphics::update_pond(WINDOW* window) {
    const int capacity = meadow.pond->get_capacity();
    const int number_of_animals = meadow.pond->get_number_of_animals();
    const std::string info = "Capacity: " + std::to_string(capacity);
    const char *c_info = info.c_str();   // TODO - make it a function

    const std::string animals_info = "Drinking: " + std::to_string(number_of_animals);
    const char *c_animals_info = animals_info.c_str();

    mvwprintw(window, 4, 3, "POND");
    mvwprintw(window, 5, 3, c_info);
    mvwprintw(window, 6, 13, "  ");
    mvwprintw(window, 6, 3, c_animals_info);
    wrefresh(window);
}

void Graphics::update_rabbit_holes(WINDOW* window) {
    const int capacity = rabbit_holes.at(0)->get_capacity();
    const std::string info = "Capacity: " + std::to_string(capacity);
    const char *c_info = info.c_str();   // TODO - make it a function

    mvwprintw(window, 4, (max_x - 87), "RABBIT HOLES");
    mvwprintw(window, 5, (max_x - 87), c_info);

    for (int i = 0; i < rabbit_holes.size(); ++i) {
        Rabbit_Hole *rabbit_hole = rabbit_holes.at(i);
        const int number_of_animals = rabbit_hole->get_number_of_animals();
        const std::string animals_info = "Hiding: " + std::to_string(number_of_animals);
        const char *c_animals_info = animals_info.c_str();
        mvwprintw(window, 6 + i, (max_x - 87) + 8, "  ");
        mvwprintw(window, 6 + i, (max_x - 87), c_animals_info);
    }

    wrefresh(window);
}

void Graphics::draw_results() {
    WINDOW *sun_window = newwin(20, (max_x - 70), 0, 35);
    wrefresh(sun_window);

    WINDOW *rabbits_window = newwin(20, (max_x - 70) / 3, 13, 35 + (max_x - 70) / 3);
    mvwprintw(rabbits_window, 1, (max_x - 70) / 6 - 4, "RABBITS");
    mvwhline(rabbits_window, 3, 0, ACS_HLINE, (max_x - 70) / 3);
    box(rabbits_window, 0, 0);
    wrefresh(rabbits_window);

    WINDOW *cows_window = newwin(20, (max_x - 70) / 3, 13, 35);
    mvwprintw(cows_window, 1, (max_x - 70) / 6 - 2, "COWS");
    mvwhline(cows_window, 3, 0, ACS_HLINE, (max_x - 70) / 3);
    box(cows_window, 0, 0);
    wrefresh(cows_window);

    WINDOW *wolves_window = newwin(20, (max_x - 70) / 3, 13, 35 + (max_x - 70) / 3 * 2);
    mvwprintw(wolves_window, 1, (max_x - 70) / 6 - 3, "WOLVES");
    mvwhline(wolves_window, 3, 0, ACS_HLINE, (max_x - 70) / 3);
    box(wolves_window, 0, 0);
    wrefresh(wolves_window);

    int sun_progress_index = 0;
    int sun_prev_progress = 0;

    std::vector<int> rabbits_progress_index;
    std::vector<int> rabbits_prev_progress;
    for (int i = 0; i < rabbits.size(); i++) {
        rabbits_progress_index.push_back(0);
        rabbits_prev_progress.push_back(0);
    }

    std::vector<int> cows_progress_index;
    std::vector<int> cows_prev_progress;
    for (int i = 0; i < cows.size(); i++) {
        cows_progress_index.push_back(0);
        cows_prev_progress.push_back(0);
    }

    std::vector<int> wolves_progress_index;
    std::vector<int> wolves_prev_progress;
    for (int i = 0; i < wolves.size(); i++) {
        wolves_progress_index.push_back(0);
        wolves_prev_progress.push_back(0);
    }

    draw_sun(sun_window);

    do {
        update_rabbits(rabbits_window, rabbits_progress_index, rabbits_prev_progress);
        update_cows(cows_window, cows_progress_index, cows_prev_progress);
        update_wolves(wolves_window, wolves_progress_index, wolves_prev_progress);
        update_sun(sun_window, sun_prev_progress, sun_progress_index);
        update_pond(sun_window);
        update_rabbit_holes(sun_window);
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } while (meadow.ready);

}

void Graphics::update_sun(WINDOW *window, int &prev_progress, int &progress_index) {
    //mutex ?
    bool is_day = sun.getIsDay();
    int progress = sun.getProgress();

    int x = 56;
    int y = 2;

    update_progress_bar(window, prev_progress, progress_index, progress, x, y);

    std::string state = is_day ? "DAY  " : "NIGHT";
    const char *cstate = state.c_str();
    mvwprintw(window, 1, 60, cstate);

    wrefresh(window);
}

void Graphics::update_progress_bar(WINDOW *window, int &prev_progress, int &progress_index, int progress, int x, int y) {
    const char *c_progress_info = (std::to_string(progress) + " %% ").c_str();
    progress = Utils::round_up(progress);

    if (progress <= 100) {
        if (prev_progress != progress) {
            mvwaddch(window, y, x + progress_index , '#');
            progress_index++;
            prev_progress = progress;
        }
    }
    if (progress_index > 10) {
        wmove(window, y, x);
        wclrtoeol(window);
        progress_index = 0;
        prev_progress = 0;
    }

    mvwprintw(window, y, x - 1, "[");
    mvwprintw(window, y, x + 10, "]");
    mvwprintw(window, y, x + 13, c_progress_info);
}

void Graphics::draw_sun(WINDOW *window) {
    wattron(window, COLOR_PAIR(2));
    mvwprintw(window, 3, 50, "           |");
    mvwprintw(window, 4, 50, "     \\     |     /");
    mvwprintw(window, 5, 50, "       \\       /");
    mvwprintw(window, 6, 50, "         ,d8b,");
    mvwprintw(window, 7, 60, "88888 ---");
    mvwprintw(window, 8, 61, "8P'");
    mvwprintw(window, 9, 65, "\\");
    mvwprintw(window, 10, 50, "           |     \\");
    mvwprintw(window, 11, 50, "           |");
    wattroff(window, COLOR_PAIR(2));

    wattron(window, COLOR_PAIR(6));
    mvwprintw(window, 7, 50, " (')-\")_");
    mvwprintw(window, 8, 50, "('-  (. ')9'");
    mvwprintw(window, 9, 50, " '-.(PjP)'");

    mvwprintw(window, 5, 75, ".,");
    mvwprintw(window, 6, 72, ";';'  ';'.");
    mvwprintw(window, 7, 70, "';.,;    ,;");
    mvwprintw(window, 8, 74, "'.';.'");
    wattroff(window, COLOR_PAIR(6));

    wrefresh(window);
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
