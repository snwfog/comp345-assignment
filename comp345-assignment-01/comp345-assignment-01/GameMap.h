//
//  GameMap.h
//  comp345-assignment-01
//
//  Created by Chao Yang on 11-10-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GAMEMAP_H
#define GAMEMAP_H
#include "GameObjectType.h"

namespace COMP345 {    
    // maximum width of stdscr
    const int STD_X = 80-16;
    // maximum height of stdscr
    const int STD_Y = 25-1;
    
    class GameMap {
    private:
        GameObject gameObjectDatabase[STD_Y][STD_X];
    public:
        GameMap();
        GameMap(GameObject[STD_Y][STD_X]);
        friend class MapEditor;
    };

}
#endif
