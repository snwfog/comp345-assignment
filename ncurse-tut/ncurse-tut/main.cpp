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

enum GameObjectType { EMPTY = 0, WALL = '#', MONSTER = 'x', PLAYER = 'A', CHEST = 'o' };
struct Cursor {
    int x;
    int y;
    Cursor(int y, int x);
    Cursor();
};

struct GameObject {
    int x;
    int y;
    GameObjectType object;
    GameObject(int y, int x, GameObjectType type);
    GameObject();
};


WINDOW* createLegend();
WINDOW* createDialog();
void updateCursorLocation(int y, int x);
void enterEditMode();
void saveMap();
void moveCursor(int c);
void insertObjectAtCurrentPosition(int c);
void clearWindow(WINDOW* window, int attributes);
void clearWindow(WINDOW* window);
GameObject getGameObjectAtCurrentPosition();

WINDOW* wlegend;
WINDOW* wdialog;

Cursor::Cursor(int y, int x) : x(x), y(y) { }
Cursor::Cursor() : x(0), y(0) { }

GameObject::GameObject(int y, int x, GameObjectType type) : y(y), x(x), object(type) { }
GameObject::GameObject() : y(0), x(0), object(EMPTY) { }

Cursor cursor(0, 0);
GameObject db[25][80] = { GameObject() };


int main (int argc, const char * argv[])
{
    initscr();
    noecho();
    curs_set(0);
    raw();
    keypad(stdscr, TRUE);
    refresh();
    
    int std_y;
    int std_x;
    getmaxyx(stdscr, std_y, std_x);

    wlegend = createLegend();
    wdialog = createDialog();
    
    // setting the initial cursor location
    updateCursorLocation((getmaxy(stdscr)-1)/2, (getmaxx(stdscr)-16)/2);
    enterEditMode();

    endwin();
    return 0;
}

WINDOW* createLegend() {
    wlegend = newwin(getmaxy(stdscr), 16, 0, getmaxx(stdscr)-16);
    wborder(wlegend, '|', '|', '-', '-', '+', '+', '+', '+');
    // getmaxyx(wlegend, legend_y, legend_x);
    // box(wlegend, 0, 0);
    //box(stdscr, 0, 0);  
    
    mvwprintw(wlegend, 1, 1, "LEGEND    ");
    
    mvwprintw(wlegend, 3, 1, " # (w)all");
    mvwprintw(wlegend, 4, 1, " A (p)layer");
    mvwprintw(wlegend, 5, 1, " o (c)hest");
    mvwprintw(wlegend, 6, 1, " x (m)onster");  
    
    mvwprintw(wlegend, 8, 1, "EXTRA OPTIONS");
    mvwprintw(wlegend, 9, 1, " (a)uto walls");
    mvwprintw(wlegend, 10, 1, " (d)oor");
    
    mvwprintw(wlegend, 12, 1, " (r)emove");
    mvwprintw(wlegend, 13, 1, " (s)ave map");
    mvwprintw(wlegend, 14, 1, " (q)uit");
    wrefresh(wlegend);
    
    return wlegend;
}

WINDOW* createDialog() {
    wdialog = newwin(1, getmaxx(stdscr)-16, getmaxy(stdscr)-1, 0);
    // wborder(wdialog, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(wdialog);
    
    return wdialog;
}

void updateCursorLocation(int y, int x) {
    if (!(y >= getmaxy(stdscr)-1 || y < 0 || x >= getmaxx(stdscr)-16 || x < 0)) {
        GameObject tmpObj = db[cursor.y][cursor.x];
        if (tmpObj.object == EMPTY) {        
            mvwprintw(stdscr, cursor.y, cursor.x, " ");
        } else if (tmpObj.object != EMPTY) {
            mvwprintw(stdscr, cursor.y, cursor.x, "%c", tmpObj.object);
        }
        cursor.x = x;
        cursor.y = y;
        GameObject gameObjectAtNextPosition = db[y][x];
        if (gameObjectAtNextPosition.object == EMPTY) {
            attron(A_BLINK);
            mvwprintw(stdscr, y, x, "_");
            attroff(A_BLINK);
            refresh();
        } else {
            attron(A_BLINK | A_UNDERLINE);
            mvwprintw(stdscr, y, x, "%c", gameObjectAtNextPosition.object);
            attroff(A_BLINK | A_UNDERLINE);
            refresh();
        }
        clearWindow(wdialog);
        mvwprintw(wdialog, 0, 0, "Cursor: %dY, %dX", cursor.y, cursor.x);
        wrefresh(wdialog);
    }
}

void enterEditMode() {
    int c;
    while ((c = getch()) != 'q') {
        switch (c) {
            case KEY_LEFT:
            case KEY_RIGHT:
            case KEY_UP:
            case KEY_DOWN:
                moveCursor(c);
                break;
            case 'w':
            case 'p':
            case 'c':
            case 'm':
            case 'r':
                insertObjectAtCurrentPosition(c);
                break;
            default:
                mvwprintw(wdialog, 0, 0, "Error: Unrecognized option. ");
                wrefresh(wdialog);
                break;
        }        
    }
    saveMap();
}

void saveMap() {
    clearWindow(wdialog);
    
    wattron(wdialog, A_STANDOUT);
    nodelay(stdscr, FALSE);
    mvwprintw(wdialog, 0, 0, "Save before exit? <y/n>");
    wrefresh(wdialog);
    if (getch() == 'y') {
        mvwprintw(wdialog, 0, 0, "Map saved to the current map collection!");
    } else {
        clearWindow(wdialog, A_STANDOUT);  
        mvwprintw(wdialog, 0, 0, "Map NOT saved!");
    }
    wattroff(wdialog, A_STANDOUT);
    wrefresh(wdialog);
    usleep(1000000);
}

void moveCursor(int c) {
    switch (c) {
        case KEY_LEFT:
            updateCursorLocation(cursor.y, cursor.x-1);
            break;
        case KEY_RIGHT:
            updateCursorLocation(cursor.y, cursor.x+1);
            break;
        case KEY_UP:
            updateCursorLocation(cursor.y-1, cursor.x);
            break;
        case KEY_DOWN:
            updateCursorLocation(cursor.y+1, cursor.x);
            break;
        default:
            break;
    }
}

void insertObjectAtCurrentPosition(int c) {
    GameObjectType type;
    switch (c) {
        case 'w':
            type = WALL;
            break;
        case 'p':
            type = PLAYER;
            break;
        case 'm':
            type = MONSTER;
            break;
        case 'c':
            type = CHEST;
            break;
        case 'r':
            type = EMPTY;
        default:
            // type = EMPTY;
            break;
    }
    db[cursor.y][cursor.x] = GameObject(cursor.y, cursor.x, type);
    mvwprintw(stdscr, cursor.y, cursor.x, "%c", db[cursor.y][cursor.x].object);
    wrefresh(wdialog);
}

void clearWindow(WINDOW* window, int attributes) {
    wattroff(wdialog, A_ATTRIBUTES);
    for (int y = 0; y < getmaxy(window); y++) {
        for (int x = 0; x < getmaxx(window); x++) {
            wmove(window, y, x);
            waddch(window, ' ');
        }
    }
    wattron(window, attributes);
    wrefresh(window);
}

void clearWindow(WINDOW* window) {
    wattroff(wdialog, A_ATTRIBUTES);
    for (int y = 0; y < getmaxy(window); y++) {
        for (int x = 0; x < getmaxx(window); x++) {
            wmove(window, y, x);
            waddch(window, ' ');
        }
    }
    wrefresh(window);
}

bool cursorOutOfBound() {
    return false;
}
