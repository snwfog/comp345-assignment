//
//  GameMap.cpp
//  comp345-assignment-01
//
//  Created by Chao Yang on 11-10-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "GameMap.h"

namespace COMP345 {
    
    
    // constructor for game map
    GameMap::GameMap() {
        // initialize everything to empty space
        for (int j = 0; j < STD_Y; j++) {
            for (int i = 0; i < STD_X; i++)
                gameObjectDatabase[j][i] = GameObject();
        }
    }

    GameMap::GameMap(GameObject importeddb[STD_Y][STD_X]) {
        for (int j = 0; j < STD_Y; j++) {
            for (int i = 0; i < STD_X; i++)
                gameObjectDatabase[j][i] = importeddb[j][i];
        }
    }
}