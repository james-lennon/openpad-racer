//
//  car.cpp
//  RacingGame
//
//  Created by James Lennon on 1/16/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "car.h"
#include "TrackScreen.h"

Car::Car(){
    track = nullptr;
    pos = 0;
    speed = 0;
    margin = scalex = scaley = 0;
    offset = 0;
}

void Car::update(float dt){
    float realspeed = speed / 100 * getTrack().size();
    pos += realspeed * dt;
    if(pos >= getTrack().size()){
        pos -= getTrack().size();
    }
}

void Car::draw(sf::RenderWindow &window){
    dot.setFillColor(col);
    drawTrack(window);
    dot.setRadius(10);
    pair<int, int> loc = getTrack()[getPos()];
    expand(loc);
    dot.setPosition(loc.first - dot.getLocalBounds().width/2 + offset, loc.second-dot.getLocalBounds().height/2);
    
    window.draw(dot);
}

void Car::drawTrack(RenderWindow& window){
    int thickness = 3;
    for(int i=0; i<getTrack().size(); i++){
        Vertex lis[] =
        {
            Vector2f(margin+getTrack()[i].first*scalex+offset, margin+getTrack()[i].second*scaley),
            Vector2f(margin+getTrack()[(i+thickness)%getTrack().size()].first*scalex + offset, margin+getTrack()[(i+thickness)%getTrack().size()].second*scaley)
        };
//                lis[0].color = Color::Red;
//                lis[1].color = Color::Blue;
        lis[0].color = lis[1].color = col;
        window.draw(lis, 2, PrimitiveType::LinesStrip);
        
        //        CircleShape dot;
        //        dot.setRadius(thickness);
        //        dot.setFillColor(Color::White);
        //        dot.setPosition(margin+track[i].first*scalex, margin+track[i].second*scaley);
        //        window.draw(dot);
        
        //        RectangleShape line;
    }
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


void Car::setTrack(vector<pair<int,int> >& t){
    track = &t;
}

vector<pair<int,int> >& Car::getTrack(){
    return *track;
}

void Car::expand(pair<int, int> &loc){
    loc.first = margin+loc.first*scalex;
    loc.second = margin+loc.second*scaley;
}

CarManager::CarManager(){
    
}

void CarManager::setValues(vector<pair<int, int> > &track, float scalex, float scaley, float margin){
    for (int i=0; i<size(); i++) {
        cars[i]->scalex = scalex;
        cars[i]->scaley = scaley;
        cars[i]->margin = margin;
        cars[i]->setTrack(track);
        cars[i]->offset = i*30;
    }
}

void CarManager::draw(sf::RenderWindow &window){
    for(int i=0; i<size(); i++){
        cars[i]->draw(window);
    }
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

