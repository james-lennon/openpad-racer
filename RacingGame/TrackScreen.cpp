//
//  TrackScreen.cpp
//  RacingGame
//
//  Created by James Lennon on 1/15/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "TrackScreen.h"

void TrackScreen::show(sf::RenderWindow &window){
    mapx = 200;
    mapy = 200;
    margin = 50;
    scalex = (window.getSize().x - margin)/mapx;
    scaley = (window.getSize().y - margin)/mapy;
    
    _gen = new Generator(mapx,mapy,6);
    _gen->generate();
    
    Car c, c2, c3, c4;
    c.col = Color::Red;
    c2.col = Color::Blue;
    c3.col = Color::Green;
    c4.col = Color::Yellow;
    c2.setSpeed(10);
    c.setSpeed(20.0);
    c3.setSpeed(15);
    c4.setSpeed(16);
    CarManager man;
    man.addCar(c);
    man.addCar(c2);
    man.addCar(c3);
    man.addCar(c4);
    
    man.setValues(_gen->track_list, scalex, scaley, margin);
    
    Clock clock;
    
    while(window.isOpen()){
        sf::Event evt;
        while(window.pollEvent(evt)){
            if(evt.type == Event::Closed || (evt.type == Event::KeyPressed && evt.key.code == sf::Keyboard::Escape)){
                Game::exit();
            }else if(evt.type == Event::KeyPressed){
                if(evt.key.code == Keyboard::Space){
                    _gen->generate();
                    man.setValues(_gen->track_list, scalex, scaley, margin);
                }
            }
        }
        
        window.clear(Color::Black);
        float dt = clock.restart().asSeconds();
        man.update(dt);
        man.draw(window);
        window.display();
    }
}