//
//  VisualizerScreen.h
//  OpenpadRacer
//
//  Created by James Lennon on 1/17/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#ifndef __OpenpadRacer__VisualizerScreen__
#define __OpenpadRacer__VisualizerScreen__

#include <stdio.h>
#include "stdafx.h"
#include "generator.h"

class VisualizerScreen: public Screen {
    
public:
    virtual void show(RenderWindow & window);
    void drawTrack(RenderWindow& window);
    static bool showTrack;
    
private:
    Generator* _gen;
    double scalex, scaley;
    int mapx, mapy;
    int margin;
    Text players;
    
    void displayPlayers(RenderWindow& window);
};

#endif /* defined(__OpenpadRacer__VisualizerScreen__) */
