//
//  MapEditor.h
//  comp345-assignment-01
//
//  Created by Chao Yang on 11-09-30.

#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include <iostream>
#include <ncurses.h>

#include "GameMap.h"

namespace COMP345 {
        
    // structure to represent the cursor
    struct Cursor {
        int y, x;
        Cursor(int, int);
        Cursor();
    };

    // forward declare GameMap
    // class GameMap;
    
    class MapEditor {
    private:
        // instance variables
        WINDOW* pwLegend; // pointer to the legend window
        WINDOW* pwDialog; // pointer to the dialog window
        GameObject player; // a unique player object
        Cursor cursor; // a unique cursor object
        GameObject gameObjectDatabase[STD_Y][STD_X]; // a game objects database
        
        // helper functions
        WINDOW* createLegendWindow();
        WINDOW* createDialogWindow();
        void moveCursorPositionTo(int, int);
        void wclear(WINDOW*, int);
        void wclear(WINDOW*);
        void enterEditMode();
        void mvCursor(int);
        void insertGameObjectAtCurrentPosition(int);
        void insertGameObjectAtPosition(int, int, GameObject);
        void buildAutoWalls();
        void saveMap();
        void refreshstdscrFromGameObjectDatabase();
    public:
        MapEditor();
        MapEditor(GameMap map);
        //~MapEditor();
    };
}
#endif
