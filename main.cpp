#include <iostream>

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include <jsoncpp/json/json.h>
#include <ncurses.h>

#include "netutility.h"
#include "colors.h"
using namespace std;

void PrintTitle(WINDOW *win,const char *msg);

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
        printf(FRED("Terminal window is too small!\n"));
        endwin();
        return 0;
    }

    list = newwin(h / 2 - 1, w - 2, 1, 1);
    form = newwin(h / 2, w / 2, h / 2, w / 2);

    box(stdscr, 0, 0);
    box(list, 0, 0);
    box(form, 0, 0);
    PrintTitle(stdscr, "netUtility");
    PrintTitle(form, "Connect");
    scrollok(list, TRUE);

    refresh();
    wrefresh(form);
    for (int i = 0; i < 10; i++){
        mvwprintw(list, i + 1, 1, "Govno");
        wrefresh(list);
    }

    pause();
    endwin();
    return 0;
}

void PrintTitle(WINDOW *win,const char *msg)
{
    int col, row;
    getmaxyx(win, row, col);
    mvwprintw(win, 0, col / 2 - strlen(msg), msg);
}
