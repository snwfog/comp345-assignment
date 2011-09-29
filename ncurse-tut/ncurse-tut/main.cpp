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
    // This function will not write out what you have entered from the getch() function
    noecho();
    // Hide the blinking cursor
    curs_set(0);
//    move(0, 1);
//    printw("Hello World !!!");
    // above 2 functions can be condensed into single function
    
    // Initialize a color pair (background and foreground)
    init_pair(1, COLOR_RED, COLOR_RED);
    WINDOW* legend = newwin(10, getmaxx(stdscr), getmaxy(stdscr)-10, 0);
    int c;
    int y, x;
    string str("Keycode: %d, and the character is: %c");
    int stringlength = str.length() - 2;
    
    // Return the maximum height and width of the standard screen
    getmaxyx(stdscr, y, x);
    

    printw("Write something (ESC to escape): ");
//    refresh();
    while ((c = getch()) != 27) {
        move(y/2, (x-stringlength)/2);
        // Enable the attributes
        
        attron(A_REVERSE | COLOR_PAIR(1));
        printw("Keycode: %d, and the character is: %c", c, static_cast<char>(c));
        attroff(A_REVERSE | COLOR_PAIR(1));
        move(0, 0);
        printw("Write something (ESC to escape): ");
        refresh();
    }
    endwin();
    
    return 0;
}

