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

class Car {
    
public:
    Car();
    void update(float dt);
    float getPos();
    void setPos(float pos);
    float getSpeed();
    void setSpeed(float speed);
    
private:
    float pos, speed;
};

class CarManager{
    
public:
    CarManager();
    void setTrack();
    void addCar(Car &c);
    void update(float dt);
    Car& getCar(int index);
    int size();
    void clear();
    
private:
    vector<Car*> cars;
    
};

#endif /* defined(__RacingGame__car__) */
