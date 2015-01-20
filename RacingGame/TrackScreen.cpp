//
//  TrackScreen.cpp
//  RacingGame
//
//  Created by James Lennon on 1/15/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "TrackScreen.h"

Color TrackScreen::color_list[] = {Color::Red, Color::Yellow, Color::Green, Color::Blue};
map<string, Car*> TrackScreen::cars;

void TrackScreen::setPlayers(vector<string> ids){
    for(map<string,Car*>::iterator it = cars.begin(); it!=cars.end(); ++it){
        delete it->second;
    }
    cars.clear();
    for(int i=0; i<ids.size(); i++){
        Car* c = new Car;
        c->col = color_list[i];
        cars[ids[i]] = c;
    }
}

void TrackScreen::handleInput(string id, openpad::PadUpdateObject update){
    if(update.controlid!=0)return;
    if (update.action == ACTION_DOWN) {
        cars[id]->accelerate();
    }else if(update.action == ACTION_UP){
        cars[id]->brake();
    }
}

void TrackScreen::show(sf::RenderWindow &window){
    mapx = 200;
    mapy = 200;
    margin = 50;
    scalex = (window.getSize().x - margin)/mapx;
    scaley = (window.getSize().y - margin)/mapy;
    
    _gen = new Generator(mapx,mapy,6);
    _gen->generate();
    
    /*
    Car c, c2, c3, c4;
    c.col = Color::Red;
    c2.col = Color::Blue;
    c3.col = Color::Green;
    c4.col = Color::Yellow;
    c2.setSpeed(10);
    c.setSpeed(15.0);
    c3.setSpeed(15);
    c4.setSpeed(16);
    man.addCar(c);
    man.addCar(c2);
    man.addCar(c3);
    man.addCar(c4);
    */
    
    CarManager man;
    for(map<string,Car*>::iterator it = cars.begin(); it!=cars.end(); ++it){
        man.addCar(*it->second);
    }
    man.setValues(_gen->track_list, scalex, scaley, margin);
    
    Clock clock;
    
    while(window.isOpen()){
        sf::Event evt;
        while(window.pollEvent(evt)){
            if(evt.type == Event::Closed || (evt.type == Event::KeyPressed && evt.key.code == sf::Keyboard::Escape)){
                Game::exit();
            }else if(evt.type == Event::KeyPressed){
//                if(evt.key.code == Keyboard::Space){
//                    _gen->generate();
//                    man.setValues(_gen->track_list, scalex, scaley, margin);
//                }
            }
        }
        
        window.clear(Color::Black);
        float dt = clock.restart().asSeconds();
        man.update(dt);
        man.draw(window);
        window.display();
    }
}

void TrackScreen::disconnectCar(string id){
    cars[id]->disconnect();
}