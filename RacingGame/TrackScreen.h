//
//  TrackScreen.h
//  RacingGame
//
//  Created by James Lennon on 1/15/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#ifndef __RacingGame__TrackScreen__
#define __RacingGame__TrackScreen__

#include <stdio.h>
#include <map>
#include <vector>
#include "stdafx.h"
#include "car.h"
#include "generator.h"

using namespace std;
using namespace openpad;

class TrackScreen: public Screen {
    
public:
    static Color color_list[];
    
    virtual void show(RenderWindow & window);
    static void setPlayers(vector<string> ids);
    static void disconnectCar(string id);
    static void handleInput(string id, PadUpdateObject update);
    
private:
    
    Generator* _gen;
    double scalex, scaley;
    int mapx, mapy;
    int margin;
    static map<string, Car*> cars;
};

#endif /* defined(__RacingGame__TrackScreen__) */
