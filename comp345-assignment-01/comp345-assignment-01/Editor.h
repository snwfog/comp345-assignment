//
//  Editor.h
//  comp345-assignment-01
//
//  Created by Chao Yang on 11-10-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef EDITOR_H
#define EDITOR_H

#include <iostream>
#include <vector>
#include "GameMap.h"
#include "MapEditor.h"

namespace COMP345 {
    class Editor {
    public:
        Editor();
        friend class MapEditor;
    private:
        static std::vector<GameMap> mapdb;
    };
}
#endif
