//
//  MapEditor.h
//  comp345-assignment-01
//
//  Created by Chao Yang on 11-09-30.

#include <iostream>
#include <ncurses.h>

#ifndef MAPEDITOR_H
#define MAPEDITOR_H

namespace COMP345 {
    
    // maximum width of stdscr
    const int STD_X = 80;
    // maximum height of stdscr
    const int STD_Y = 25;
    
    // character representation of the game objects
    enum GameObjectType { EMPTY = 32, WALL = '#', MONSTER = 'x', PLAYER = 'A', CHEST = 'o' };
    
    // structure to represent the cursor
    struct Cursor {
        int y, x;
        Cursor(int y, int x);
        Cursor();
    };
    
    // structure to represent the game object
    struct GameObject {
        int y, x;
        GameObjectType object;
        GameObject(int y, int x, GameObjectType type);
        GameObject();
    };
    
    class MapEditor {
    private:
        // instance variables
        WINDOW* pwLegend; // pointer to the legend window
        WINDOW* pwDialog; // pointer to the dialog window
        GameObject player; // a unique player object
        Cursor cursor; // a unique cursor object
        // Cursor cursor(0, 0); ???
        GameObject gameObjectDatabase[STD_Y][STD_X]; // a game objects database
        
        // helper functions
        WINDOW* createLegendWindow();
        WINDOW* createDialogWindow();
        void updateCursorPosition(int y, int x);
    public:
        MapEditor();
        ~MapEditor();
    };
}
#endif
