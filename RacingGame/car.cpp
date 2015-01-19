//
//  car.cpp
//  RacingGame
//
//  Created by James Lennon on 1/16/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "car.h"
#include <cmath>

Car::Car(){
    track = nullptr;
    margin = scalex = scaley = 0;
    offset = 0;
    reset();
}

void Car::reset(){
    offTrack = false;
    pos = 0;
    speed = 0;
    acceleration = 0;
}

float magnitude(Vector2f &vec){
    return sqrt(vec.x*vec.x+vec.y*vec.y);
}

float Car::calcCentAcc(float dt){
    Vector2f acc = (vel - prevVel)/dt;
    if (magnitude(acc)==0) {
        return 0.f;
    }
    float dotproduct = acc.x*vel.x+acc.y*vel.y;
    float magproduct = magnitude(acc)*magnitude(vel);
    float theta = acos(dotproduct/magproduct);
    float ac = magnitude(acc)*sin(theta);
//    printf("theta: %f, a: %f, ac: %f\n",theta, magnitude(acc), ac);
    return ac;
}

void Car::accelerate(){
    acceleration = Constants::car_acc;
}

void Car::brake(){
    acceleration = -2*Constants::car_acc;
}

void Car::update(float dt){
    if(offTrack){
        if(offTimer.getElapsedTime().asSeconds()<3){
            offPos += vel * dt;
            //            vel /= (2.0f*dt);
            if(abs(vel.x)>0.1){
                vel.x -= Constants::car_acc*2*dt;
            }
            if(abs(vel.y)>0.1){
                vel.y -= Constants::car_acc*2*dt;
            }
        }else{
            offTrack = false;
        }
        return;
    }
    if(abs(acceleration)>0){
        speed += acceleration * dt;
        if(speed<0)speed = 0;
    }
    prevVel = vel;
    int delta = 4;
    vel = Vector2f(getTrack()[(int)pos].first - getTrack()[(int)(pos-delta+getTrack().size())%getTrack().size()].first, getTrack()[(int)pos].second - getTrack()[(int)(pos-delta+getTrack().size())%getTrack().size()].second) * speed;
    
    float realspeed = speed / 100 * getTrack().size();
    pos += realspeed * dt;
    if(pos >= getTrack().size()){
        pos -= getTrack().size();
    }
    if(calcCentAcc(dt)>Constants::acc_tolerance){
        knockOff();
    }
}

void Car::knockOff(){
    speed = 0;
    prevVel = {0,0};
    vel *= 3.0f;
    offTrack = true;
    offTimer.restart();
    pair<int, int> tloc = getTrack()[(int)pos];
    expand(tloc);
    offPos.x = tloc.first;
    offPos.y = tloc.second;
}

void Car::draw(sf::RenderWindow &window){
    dot.setFillColor(col);
    dot.setRadius(10);
    drawTrack(window);
    if(offTrack){
        dot.setPosition(offPos);
    }else{
        pair<int, int> loc = getTrack()[getPos()];
        expand(loc);
        dot.setPosition(loc.first - dot.getLocalBounds().width/2 + offset, loc.second-dot.getLocalBounds().height/2);
    }
    
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

void Car::disconnect(){
    col = Color(100, 100, 100);
    speed = 0;
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

