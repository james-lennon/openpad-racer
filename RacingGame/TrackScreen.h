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
#include "stdafx.h"
#include "generator.h"
#include "car.h"

class TrackScreen: public Screen {
    
public:
    virtual void show(RenderWindow & window);
    
private:
    void drawTrack(vector<pair<int,int>> track, RenderWindow & window);
    void drawCar(Car& c, sf::RenderWindow &window);
    void expand(pair<int,int> &loc);
    
    Generator *_gen;
    double scalex, scaley;
    int mapx, mapy;
    int margin;
};

#endif /* defined(__RacingGame__TrackScreen__) */
