//
//  main.cpp
//  ncurse-tut
//
//  Created by Chao Yang on 11-09-28.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <string>
#include "ncurses.h"
using std::string;

int main (int argc, const char * argv[])
{
    initscr();
    noecho();
    raw();
    
    // enable the arrow keys and F functions
    keypad(stdscr, TRUE);
    // hide the cursor
    // curs_set(0);
    
    WINDOW* wlegend = newwin(1, getmaxx(stdscr), getmaxy(stdscr)-1, 0);
    // box(wlegend, 0, 0);
    // box(stdscr, 0, 0);
    
    mvprintw(getmaxy(stdscr)-2, getmaxx(stdscr)-1, "b");
    refresh();
    
    mvwprintw(wlegend, getmaxy(wlegend)-1, getmaxx(wlegend)-1, "a");
    //mvwprintw(wlegend, 0, 0, "The wlegend height: %d, width: %d.", getmaxy(wlegend), getmaxx(wlegend));
    wrefresh(wlegend);
    
    getch();
    endwin();
    
    return 0;
}

