//
//  GameMap.h
//  comp345-assignment-01
//
//  Created by Chao Yang on 11-10-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef GAMEMAP_H
#define GAMEMAP_H

namespace COMP345 {
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
