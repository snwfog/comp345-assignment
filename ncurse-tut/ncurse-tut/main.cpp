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
    curs_set(0);
    raw();
    
    bool isSaved;
    int std_y;
    int std_x;
    int legend_y;
    int legend_x;
    
    getmaxyx(stdscr, std_y, std_x);
    
    // enable the arrow keys and F functions
    keypad(stdscr, TRUE);
    // hide the cursor
    // curs_set(0);
    
    refresh();
    
    WINDOW* wlegend = newwin(std_y, 16, 0, std_x-16);
    // box(wlegend, 0, 0);
    getmaxyx(wlegend, legend_y, legend_x);
    // box(wlegend, 0, 0);
    // box(stdscr, 0, 0);
    WINDOW* wdialog = newwin(1, std_x-16, std_y-1, 0);
    // box(wdialog, 0, 0);
    wrefresh(wdialog);
    

    mvwprintw(wlegend, 1, 1, "### LEGEND ###");
    mvwprintw(wlegend, 3, 1, " + (W)all");
    mvwprintw(wlegend, 4, 1, " + (P)layer");
    mvwprintw(wlegend, 5, 1, " + (C)hest");
    mvwprintw(wlegend, 6, 1, " + (M)onster");
    mvwprintw(wlegend, 8, 1, " + (S)ave Map");
    mvwprintw(wlegend, 9, 1, " + (Q)uit");
    //mvwprintw(wlegend, 0, 0, "The wlegend height: %d, width: %d.", getmaxy(wlegend), getmaxx(wlegend));
    wrefresh(wlegend);
    
    int c;
    do {
        switch (c = getch()) {
            case 'q':
                if (getch() == static_cast<int>('y')) {
                    mvwprintw(wdialog, 0, 0, "Map saved! ");
                } else if (getch() == static_cast<int>('n')) {
                    mvwprintw(wdialog, 0, 0, "Map NOT saved! ");
                }
                wrefresh(wdialog);
                usleep(500000);
                endwin();
                break;
                
            default:
                mvwprintw(wdialog, 0, 0, "You have pressed the character: %c", c);
                wrefresh(wdialog);
                break;
        }
    } while (true);
    
    nodelay(wdialog, FALSE);
    
    wattron(wdialog, A_STANDOUT);
    mvwprintw(wdialog, 0, 0, "Would you like to quit? <y/n>: ");
    wrefresh(wdialog);
    
    wattroff(wdialog, A_STANDOUT);
        
    endwin();
    return 0;
}

