//
//  LoadingScreen.h
//  Openpad Racer
//
//  Created by James Lennon on 1/20/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#ifndef __Openpad_Racer__LoadingScreen__
#define __Openpad_Racer__LoadingScreen__

#include <stdio.h>
#include "stdafx.h"

struct player {
    Text name;
    CircleShape dot;
};

class LoadingScreen: public Screen {
    vector<struct player> players;
    Font sans;
    Clock time;
    Text countdown;
    
public:
    virtual void show(RenderWindow & window);
    
private:
    void loadPlayers();
};

#endif /* defined(__Openpad_Racer__LoadingScreen__) */
