#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <jsoncpp/json/json.h>
#include <ncurses.h>

#include "netutility.h"
#include "colors.h"
using namespace std;

void print_middle(const char *msg);

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");

    if (getuid()) {
        printf(FRED("netUtility must be run as root!\n"));
        return 0;
    }

    initscr();
    int w, h;
    getmaxyx(stdscr, h, w);

    if(w < 90 || h < 30) {
        printf(FRED("Terminal windows is too small!\n"));
        endwin();
        return 0;
    }
    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);

    box(stdscr, 0, 0);
    attron(COLOR_PAIR(1));
    print_middle("netu");
    attroff(COLOR_PAIR(1));
    refresh();

    pause();
    endwin();
    return 0;
}

void print_middle(const char *msg)
{
    int col, row;
    getmaxyx(stdscr, row, col);
    cout << col << row << endl;
    mvprintw(0, col / 2 - strlen(msg), msg);
}
