#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <jsoncpp/json/json.h>
#include <ncurses.h>
#include "netutility.h"
#include "colors.h"
using namespace std;

void PrintTitle(WINDOW *win, const char *msg);
void PrintList(WINDOW *list, int highlight);

int   n_cons      = 128;
string  cons[128] = {"a", "b", "c", "d", "a", "b", "c", "d", "a", "b", "c", "d", "a", "b", "c", "d", "a", "b", "c", "d", "a", "b", "c", "d", "a", "b", "c", "d"};

int main(int argc, char *argv[])
{
    WINDOW *list, *form, *info;
    setlocale(LC_ALL, "");
    int selWin      = 1,
        highlight   = 1,
        choice      = 0,
        c;

    if (getuid()) {
        printf(FRED("netUtility must be run as root!\n"));
        return 0;
    }

    initscr();
    clear();
    noecho();
    cbreak();

    int w, h;
    getmaxyx(stdscr, h, w);

    if(w < 70 || h < 20) {
        printf(FRED("Terminal window is too small!\n"));
        endwin();
        return 0;
    }

    list = newwin(h / 2 - 1, w - 2, 1, 1);
    form = newwin(h / 2 - 1, w / 2 - 1, h / 2, w / 2);
    info = newwin(h / 2 - 1, w / 2 - 2, h / 2, 1);

    scrollok(list, TRUE);
    keypad(list, TRUE);

    box(stdscr, 0, 0);
    box(form, 0, 0);
    box(info, 0, 0);

    PrintTitle(stdscr, "netUtility");
    PrintTitle(form, "Connect");
    PrintTitle(info, "Info");

    refresh();
    wrefresh(form);
    wrefresh(info);

    PrintList(list, highlight);
    while(selWin == 1)
    {
        c = wgetch(list);
        switch(c)
        {
            case KEY_UP:
                if(highlight == 1)
                    highlight = n_cons;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == n_cons)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight - 1;
                break;
            case KEY_STAB:
                mvwprintw(list, 10, 20, "ПОШЕЛ НАХУЙ");
                selWin++;
                break;
            }
            PrintList(list, highlight);
            if(choice != 0)
                break;
        }
    printf(cons[choice].c_str());
    clrtoeol();
    refresh();
    endwin();
    return 0;
}

void PrintTitle(WINDOW *win, const char *msg)
{
    int col, row;
    getmaxyx(win, row, col);
    mvwprintw(win, 0, col / 2 - strlen(msg), msg);
}

void PrintList(WINDOW *list, int highlight)
{
    int x, y, i;

    x = 2;
    y = 2;
    box(list, 0, 0);
    for(i = 0; i < n_cons; ++i){
        if(highlight == i + 1) {
            wattron(list, A_REVERSE);
            mvwprintw(list, y, x, "%s", cons[i].c_str());
            wattroff(list, A_REVERSE);
        } else {
            mvwprintw(list, y, x, "%s", cons[i].c_str());
        }
        ++y;
    }
    wrefresh(list);
}
