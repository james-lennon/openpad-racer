//
//  TrackScreen.cpp
//  RacingGame
//
//  Created by James Lennon on 1/15/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "TrackScreen.h"

void TrackScreen::drawTrack(vector<pair<int, int> > track, sf::RenderWindow &window){
    float thickness = 5;
    for(int i=0; i<track.size(); i++){
        Vertex lis[] =
        {
            Vector2f(margin+track[i].first*scalex, margin+track[i].second*scaley),
            Vector2f(margin+track[(i+1)%track.size()].first*scalex, margin+track[(i+1)%track.size()].second*scaley)
        };
        window.draw(lis, 2, PrimitiveType::LinesStrip);
        
//        CircleShape dot;
//        dot.setRadius(thickness);
//        dot.setFillColor(Color::White);
//        dot.setPosition(margin+track[i].first*scalex, margin+track[i].second*scaley);
//        window.draw(dot);
        
//        RectangleShape line;
    }
}

void TrackScreen::expand(pair<int, int> &loc){
    loc.first = margin+loc.first*scalex;
    loc.second = margin+loc.second*scaley;
}

void TrackScreen::drawCar(Car &c, sf::RenderWindow &window){
    CircleShape dot;
    dot.setFillColor(Color::Red);
    dot.setRadius(10);
    pair<int, int> loc = _gen->track_list[c.getPos()];
    expand(loc);
    dot.setPosition(loc.first, loc.second);
    
    window.draw(dot);
}

void TrackScreen::show(sf::RenderWindow &window){
    mapx = 200;
    mapy = 200;
    margin = 50;
    scalex = (window.getSize().x - margin)/mapx;
    scaley = (window.getSize().y - margin)/mapy;
    
    _gen = new Generator(mapx,mapy,6);
    _gen->generate();
    
    Car c;
    c.setSpeed(20.0);
    CarManager man;
    man.addCar(c);
    
    Clock clock;
    
    while(window.isOpen()){
        sf::Event evt;
        while(window.pollEvent(evt)){
            if(evt.type == Event::Closed || (evt.type == Event::KeyPressed && evt.key.code == sf::Keyboard::Escape)){
                Game::exit();
            }else if(evt.type == Event::KeyPressed){
                if(evt.key.code == Keyboard::Space){
                    _gen->generate();
                }
            }
        }
        
        window.clear(Color::Black);
        float dt = clock.restart().asSeconds();
        man.update(dt);
        drawTrack(_gen->track_list, window);
        drawCar(man.getCar(0), window);
        window.display();
    }
}