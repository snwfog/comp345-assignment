//
//  GameObjectType.h
//  comp345-assignment-01
//
//  Created by Chao Yang on 11-10-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GAMEOBJECTTYPE_H
#define GAMEOBJECTTYPE_H

namespace COMP345 {
    // character representation of the game objects
    enum GameObjectType { EMPTY = 32, WALL = '#', MONSTER = 'x', PLAYER = 'A', CHEST = 'o' };
    
    
    // structure to represent the game object
    struct GameObject {
        int y, x;
        GameObjectType objectType;
        GameObject(int y, int x, GameObjectType type) : y(y), x(x), objectType(type) { }
        GameObject() : y(0), x(0), objectType(EMPTY) { }
    };
}

#endif
