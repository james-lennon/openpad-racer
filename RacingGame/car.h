//
//  car.h
//  RacingGame
//
//  Created by James Lennon on 1/16/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#ifndef __RacingGame__car__
#define __RacingGame__car__

#include <stdio.h>
#include <vector>
#include "stdafx.h"

using namespace std;

class Car: public GameObject {
    
public:
    Car();
    void update(float dt);
    float getPos();
    void setPos(float pos);
    float getSpeed();
    void setSpeed(float speed);
    virtual void draw(RenderWindow& window);
    void drawTrack(RenderWindow& window);
    void setTrack(vector<pair<int,int> >& track);
    vector<pair<int,int> >& getTrack();
    
    sf::Color col;
    int offset;
    float scalex, scaley, margin;
private:
    void expand(pair<int,int> &loc);
    float pos, speed;
    vector<pair<int,int> >* track;
    CircleShape dot;
};

class CarManager{
    
public:
    CarManager();
    void setValues(vector<pair<int,int> >& track, float scalex, float scaley, float margin);
    void addCar(Car &c);
    void update(float dt);
    void draw(RenderWindow& window);
    Car& getCar(int index);
    int size();
    void clear();
    
private:
    vector<Car*> cars;
    
};

#endif /* defined(__RacingGame__car__) */
