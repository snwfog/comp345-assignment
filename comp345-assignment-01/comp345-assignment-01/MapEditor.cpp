//
//  MapEditor.cpp
//  comp345-assignment-01
//
//  Created by Chao Yang on 11-09-30.

#include <iostream>
#include <ncurses.h>
#include "MapEditor.h"

namespace COMP345 {
    Cursor::Cursor(int y, int x) : y(y), x(x) { }
    Cursor::Cursor() : y(0), x(0) { }
    
    GameObject::GameObject(int y, int x, GameObjectType type) : y(y), x(x), object(type) { }
    GameObject::GameObject() : y(0), x(0), object(EMPTY) { }
    
    // constructor for mapeditor
    MapEditor::MapEditor() {
        // initializing a few ncurses handy functions
        
        // initialize the default screen, 50x80 
        initscr();
        
        // turn off echoing input
        noecho();
        
        // turn off terminal cursor
        curs_set(0);
        
        // disable the terminal line buffer
        // so the input character is immediately avaiable on input
        raw();
        
        // enable f-# function keys and the arrow keys
        keypad(stdscr, TRUE);
        
        // gives a refresh to the stdscr
        refresh();
        
        // create and display the legend and dialog window
        pwLegend = createLegendWindow();
        pwDialog = createDialogWindow();
        
        // create the gameObjectDatabase
        gameObjectDatabase = { GameObject() };
        
        // set the inital cursor location
        updateCursorPosition((STD_Y-1)/2, (STD_X-16)/2);
        
    }
    
    // create the legend window
    WINDOW* createLegendWindow() {
        // create the legend window
        WINDOW* pwTemp = newwin(STD_Y, 16, 0, STD_X-16);
        // change the border style of the legend window
        wborder(pwTemp, '|', '|', '-', '-', '+', '+', '+', '+');
        
        // print the legend text
        mvwprintw(pwTemp, 1, 1, "LEGEND    ");
        
        mvwprintw(pwTemp, 3, 1, " # (w)all");
        mvwprintw(pwTemp, 4, 1, " A (p)layer");
        mvwprintw(pwTemp, 5, 1, " o (c)hest");
        mvwprintw(pwTemp, 6, 1, " x (m)onster");  
        
        mvwprintw(pwTemp, 8, 1, " (a)uto walls");
        mvwprintw(pwTemp, 9, 1, " (d)oor");
        
        mvwprintw(pwTemp, 11, 1, " (r)emove");
        
        mvwprintw(pwTemp, 13, 1, " (s)ave map");
        mvwprintw(pwTemp, 14, 1, " (q)uit");
        
        // display the legend window
        wrefresh(pwTemp);
        return pwTemp;
    }
    
    // create the dialog window
    WINDOW* createDialogWindow() {
        WINDOW* pwTemp = newwin(1, STD_X-16, STD_Y-1, 0);
        
        // display the dialog window (empty for now)
        wrefresh(pwTemp);
        return pwTemp;
    }
    
    // update the cursor position
    void updateCursorPosition(int y, int x) {
        // check if y and x are out of the stdscr boundaries
        if (!(y >= STD_Y-1 || y < 0 || x >= STD_X-16 || x < 0)) {
            GameObject temporaryObject = gameObjectDatabase[cursor.y][cursor.x];
            
        }
    }

}