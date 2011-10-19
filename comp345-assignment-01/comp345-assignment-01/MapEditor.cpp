//
//  MapEditor.cpp
//  comp345-assignment-01
//
//  Created by Chao Yang on 11-09-30.

#include "MapEditor.h"

namespace COMP345 {
    Cursor::Cursor(int y, int x) : y(y), x(x) { }
    Cursor::Cursor() : y((STD_Y)/2), x((STD_X)/2) { }
   
    // constructor for map editor
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
        
        // fill the gameObjectDatabase
        // 1. multidimensional array are continuous inside of memory (unless some cases with pointers.
        // 2. you cannot initialize this member in the header, so must initialize it like this here
        // otherwise you could just do GameObject gameObjectDatabase[][] = { GameObject() };
        // see stackoverflow: http://stackoverflow.com/questions/3586774/fill-multidimensional-array-elements-with-0s
        // std::fill_n(gameObjectDatabase, STD_X*STD_Y, GameObject());
        //for (int j = 0; j < STD_Y; j++) {
        //    for (int i = 0; i < STD_X; i++)
        //        gameObjectDatabase[j][i] = GameObject();
        //}
        
        
        // display the initial location of the constructor
        moveCursorPositionTo((STD_Y)/2, (STD_X)/2);
        
        // go into editor mode
        enterEditMode();
        
        // WHY THIS ERROR???
        // WHY THIS ERROR???
        // cursor(1, 1); 
        // ???????????????________----------------
        
        // clean the windows
        endwin();
    }
    
    MapEditor::MapEditor(GameMap map) {
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
        
        // fill the gameObjectDatabase
        for (int j = 0; j < STD_Y; j++) {
            for (int i = 0; i < STD_X; i++)
                gameObjectDatabase[j][i] = map.gameObjectDatabase[j][i];
        }
        
        // display the initial location of the constructor
        moveCursorPositionTo((STD_Y)/2, (STD_X)/2);
        
        // go into editor mode
        enterEditMode();

        // clean the windows
        endwin();        
    }
    
    void MapEditor::enterEditMode() {
        int c;
        while ((c = getch()) != 'q') {
            switch (c) {
                case KEY_LEFT:
                case KEY_RIGHT:
                case KEY_UP:
                case KEY_DOWN:
                    mvCursor(c);
                    break;
                case 'w':
                case 'p':
                case 'c':
                case 'm':
                case 'r':
                    insertGameObjectAtCurrentPosition(c);
                    break;
                case 'a':
                    buildAutoWalls();
                    break;
                default:
                    mvwprintw(pwDialog, 0, 0, "Error: Unrecognized option. ");
                    wrefresh(pwDialog);
                    break;
            }
        }
        
        // when quitting, save the current map
        saveMap();
    }
    
    // create the legend window
    WINDOW* MapEditor::createLegendWindow() {
        // create the legend window
        WINDOW* pwTemp = newwin(STD_Y+1, 16, 0, STD_X);
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
    WINDOW* MapEditor::createDialogWindow() {
        WINDOW* pwTemp = newwin(1, STD_X, STD_Y, 0);
        
        // display the dialog window (empty for now)
        wrefresh(pwTemp);
        return pwTemp;
    }
    
    // update the cursor position
    void MapEditor::moveCursorPositionTo(int y, int x) {
        // check if y and x are out of the stdscr boundaries
        if (!(y >= STD_Y || y < 0 || x >= STD_X || x < 0)) {
            
            // update previous cursor location object
            GameObject tmpObj = gameObjectDatabase[cursor.y][cursor.x];
            if (tmpObj.objectType == EMPTY) {
                // print empty space at current cursor pos
                mvwprintw(stdscr, cursor.y, cursor.x, " ");
            } else if (tmpObj.objectType != EMPTY) {
                // print the object in the game obj db's
                mvwprintw(stdscr, cursor.y, cursor.x, "%c", tmpObj.objectType);
            }
            
            // update cursor coordinate
            cursor.x = x;
            cursor.y = y;
            // check object in the game obj db at the new position
            GameObject tmpObjAtNextPosition = gameObjectDatabase[cursor.y][cursor.x];
            if (tmpObjAtNextPosition.objectType == EMPTY) {
                // turn on the blinking attribute of stdscr
                attron(A_BLINK);
                mvwprintw(stdscr, y, x, "_");
                attroff(A_BLINK);
                refresh();
            } else {
                attron(A_BLINK | A_UNDERLINE);
                mvwprintw(stdscr, y, x, "%c", tmpObjAtNextPosition.objectType);
                attroff(A_BLINK | A_UNDERLINE);
                refresh();
            }
            
            // clean the dialog window for writing
            wclear(pwDialog);
            // print the current cursor position in the dialog window
            mvwprintw(pwDialog, 0, 0, "cursor: %dy, %dx", cursor.y, cursor.x);
            wrefresh(pwDialog);
        }
    }
    
    // clears the targeted window
    void MapEditor::wclear(WINDOW* w) {
        // turn off all attributes
        wattroff(w, A_ATTRIBUTES);
        // reset all characters on the screen to empty
        for (int y = 0; y < getmaxy(w); y++) {
            for (int x = 0; x < getmaxx(w); x++) {
                wmove(w, y, x);
                waddch(w, ' ');
            }
        }
        wrefresh(w);
    }
    
    // clears the targeted window and reapply the specified attr
    // to the targeted window
    void MapEditor::wclear(WINDOW* w, int attr) {
        wclear(w);
        wattron(w, attr);
        wrefresh(w);
    }
    
    void MapEditor::mvCursor(int c) {
        switch (c) {
            case KEY_LEFT:
                moveCursorPositionTo(cursor.y, cursor.x-1);
                break;
            case KEY_RIGHT:
                moveCursorPositionTo(cursor.y, cursor.x+1);
                break;
            case KEY_UP:
                moveCursorPositionTo(cursor.y-1, cursor.x);
                break;
            case KEY_DOWN:
                moveCursorPositionTo(cursor.y+1, cursor.x);
                break;
            default:
                break;
        }
    }
    
    void MapEditor::insertGameObjectAtCurrentPosition(int c) {
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
        
        // insert the object into the db and display in stdscr
        insertGameObjectAtPosition(cursor.y, cursor.x, GameObject(cursor.y, cursor.x, type));
    }
    
    void MapEditor::insertGameObjectAtPosition(int y, int x, GameObject gameObj) {
        
        // if type is player, update the new player position and
        // erase the old player position
        if (gameObj.objectType == PLAYER) {
            // erase the old player position from the databse
            gameObjectDatabase[player.y][player.x] = GameObject(player.y, player.x, EMPTY);
            // erase the old player position from stdscr
            mvprintw(player.y, player.x, "%c", gameObjectDatabase[player.y][player.x].objectType);
            // update the player current position;
            player.y = y;
            player.x = x;
        }
        
        // update the database at current cursor position with the currently inserted game object
        gameObjectDatabase[y][x] = gameObj;
        
        // update the stdscr at the current cursor position with the 
        // currently inserted game object character representation
        mvwprintw(stdscr, y, x, "%c", gameObjectDatabase[y][x].objectType);
        
        // print dialog about insert info
        wclear(pwDialog);
        mvwprintw(pwDialog, 0, 0, "inserted %c at %dy, %dx", gameObjectDatabase[y][x].objectType, y, x);
        
        // refresh pwDialog and stdscr
        wrefresh(pwDialog);
        refresh();
    }

    
    // this method will build auto walls starting from
    // the position of the cursor. you can specify the width
    // and the height of the wall from 0 - 9
    void MapEditor::buildAutoWalls() {
        int y1 = cursor.y;
        int x1 = cursor.x;
        int y2, x2;
        
        int c;
        
        wclear(pwDialog);
        mvwprintw(pwDialog, 0, 0, "auto wall mode on, press 'a' again to confirm wall location");
        wrefresh(pwDialog);
        
        while ((c = getch()) != 'a') {
            // allow cursor movement
            switch (c) {
                case KEY_LEFT:
                case KEY_RIGHT:
                case KEY_UP:
                case KEY_DOWN:
                    refreshstdscrFromGameObjectDatabase();
                    mvCursor(c);
                    y2 = cursor.y;
                    x2 = cursor.x;
                    
                    // create walls preview
                    for (int i = y1; i <= y2; i++) {
                        if (gameObjectDatabase[i][x1].objectType == EMPTY) {
                            mvwprintw(stdscr, i, x1, "#");
                        }
                        if (gameObjectDatabase[i][x2].objectType == EMPTY) {
                            mvwprintw(stdscr, i, x2, "#");
                        }
                    }
                    
                    for (int i = x1; i <= x2; i++) {
                        if (gameObjectDatabase[y1][i].objectType == EMPTY) {
                            mvwprintw(stdscr, y1, i, "#");
                        }
                        if (gameObjectDatabase[y2][i].objectType == EMPTY) {
                            mvwprintw(stdscr, y2, i, "#");
                        }
                    }
                    refresh();
                    break;
                default:
                    mvwprintw(pwDialog, 0, 0, "error: only arrow keys are accepted ");
                    wrefresh(pwDialog);
                    break;
            }
        }
        
        // confirm placement of the walls
        // destroying all previous data's
        for (int i = y1; i <= y2; i++) {
            gameObjectDatabase[i][x1] = GameObject(i, x1, WALL);
            gameObjectDatabase[i][x2] = GameObject(i, x2, WALL);
        }            
        for (int i = x1; i <= x2; i++) {
            gameObjectDatabase[y1][i] = GameObject(y1, i, WALL);
            gameObjectDatabase[y2][i] = GameObject(y2, i, WALL);
        }
        refreshstdscrFromGameObjectDatabase();
        
        wclear(pwDialog);
        mvwprintw(pwDialog, 0, 0, "auto wall mode completed");
        wrefresh(pwDialog);
        
    }
    
    // prints on stdscr only what is in the game object db's
    void MapEditor::refreshstdscrFromGameObjectDatabase() {
        for (int i = 0; i < STD_Y; i++) {
            for (int j = 0; j < STD_X; j++) 
                mvwprintw(stdscr, i, j, "%c", gameObjectDatabase[i][j].objectType);
        }
        
        refresh();
    }
    
    void MapEditor::saveMap() {
        wclear(pwDialog);
        
        wattron(pwDialog, A_STANDOUT);
        mvwprintw(pwDialog, 0, 0, "save before exit? <y/n>");
        wrefresh(pwDialog);
        if (getch() == 'y') {
            
            mvwprintw(pwDialog, 0, 0, "map saved to the current map collection!");
        } else {
            wclear(pwDialog, A_STANDOUT);  
            mvwprintw(pwDialog, 0, 0, "map NOT saved!");
        }
        wattroff(pwDialog, A_STANDOUT);
        wrefresh(pwDialog);
        usleep(700000);
    }
}