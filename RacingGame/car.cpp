//
//  car.cpp
//  RacingGame
//
//  Created by James Lennon on 1/16/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "car.h"

Car::Car(){
    
}

void Car::update(float dt){
    pos += speed * dt;
}

float Car::getPos(){
    return pos;
}

float Car::getSpeed(){
    return speed;
}

void Car::setPos(float _pos){
    pos = _pos;
}

void Car::setSpeed(float _speed){
    speed = _speed;
}

CarManager::CarManager(){
    
}

void CarManager::addCar(Car &c){
    cars.push_back(&c);
}

void CarManager::update(float dt){
    for (int i=0; i<size(); i++) {
        cars[i]->update(dt);
    }
}

void CarManager::clear(){
    for(int i=0; i<size(); i++){
        delete cars[i];
    }
    cars.clear();
}

int CarManager::size(){
    return cars.size();
}

Car& CarManager::getCar(int index){
    return *cars[index];
}

