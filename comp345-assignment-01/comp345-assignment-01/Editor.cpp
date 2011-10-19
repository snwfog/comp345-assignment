//
//  Editor.cpp
//  comp345-assignment-01
//
//  Created by Chao Yang on 11-10-19.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "Editor.h"

namespace COMP345 {
    Editor::Editor() {
        using namespace std;
        int opt = 0;
        while (opt != 3) {
            cout << "Welcome to the Game Editor!" << endl;
            cout << "1. Map Editor" << endl;
            cout << "2. Character Editor" << endl;
            cout << "3. Quit Editor" << endl;
            cout << "Choose your option: ";
            cin >> opt;
            switch (opt) {
                case 1: {
                    MapEditor neweditor;
                    break;
                }
                case 2: {
                    cout << "Sorry, the Character Editor  is not available yet." << endl;
                    continue;
                }
                case 3: {
                    cout << "Good bye!" << endl;
                    break;
                }
                default: {
                    cout << "Unrecognized option." << endl;
                    break;
                }
            }
        }
    }
    
    
}
