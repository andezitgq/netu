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
    WINDOW *list, *form;

    setlocale(LC_ALL, "");

    if (getuid()) {
        printf(FRED("netUtility must be run as root!\n"));
        return 0;
    }

    initscr();

    int w, h;
    getmaxyx(stdscr, h, w);

    if(w < 70 || h < 20) {
        printf(FRED("Terminal windows is too small!\n"));
        endwin();
        return 0;
    }

    list = newwin(h / 2 - 1, w - 2, 1, 1);
    form = newwin(h / 2, w / 2, h / 2, w / 2);

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);

    box(stdscr, 0, 0);
    box(list, 0, 0);
    box(form, 0, 0);
    attron(COLOR_PAIR(1));
    print_middle("netu1");
    attroff(COLOR_PAIR(1));
    scrollok(list, TRUE);

    for (int i = 0; i < 10; i++){
        wprintw(list, "Govno");
        wrefresh(list);
    }
    //refresh();
    wrefresh(list);
    wrefresh(form);

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
