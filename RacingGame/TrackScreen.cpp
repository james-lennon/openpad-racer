//
//  TrackScreen.cpp
//  RacingGame
//
//  Created by James Lennon on 1/15/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "TrackScreen.h"

int TrackScreen::track_length = 0;

void TrackScreen::drawTrack(vector<pair<int, int> > &track, Color c, float offset, sf::RenderWindow &window){
    int thickness = 2;
    for(int i=0; i<track.size(); i++){
//        if(i%2)continue;
        Vertex lis[] =
        {
            Vector2f(margin+track[i].first*scalex+offset, margin+track[i].second*scaley),
            Vector2f(margin+track[(i+thickness)%track.size()].first*scalex + offset, margin+track[(i+thickness)%track.size()].second*scaley)
        };
//        lis[0].color = Color::Red;
//        lis[1].color = Color::Blue;
        lis[0].color = lis[1].color = c;
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

void TrackScreen::drawCar(Car &c, float offset, sf::RenderWindow &window){
    CircleShape dot;
    dot.setFillColor(c.col);
    drawTrack(_gen->track_list, c.col, offset, window);
    dot.setRadius(10);
    pair<int, int> loc = _gen->track_list[c.getPos()];
    expand(loc);
    dot.setPosition(loc.first - dot.getLocalBounds().width/2, loc.second-dot.getLocalBounds().height/2);
    
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
    track_length = _gen->track_list.size();
    
    Car c, c2;
    c.col = Color::Red;
    c2.col = Color::Blue;
    c2.setSpeed(10);
    c.setSpeed(20.0);
    CarManager man;
    man.addCar(c);
    man.addCar(c2);
    
    Clock clock;
    
    while(window.isOpen()){
        sf::Event evt;
        while(window.pollEvent(evt)){
            if(evt.type == Event::Closed || (evt.type == Event::KeyPressed && evt.key.code == sf::Keyboard::Escape)){
                Game::exit();
            }else if(evt.type == Event::KeyPressed){
                if(evt.key.code == Keyboard::Space){
                    _gen->generate();
                    track_length = _gen->track_list.size();
                }
            }
        }
        
        window.clear(Color::Black);
        float dt = clock.restart().asSeconds();
        man.update(dt);
//        drawTrack(_gen->track_list, window);
        for(int i=0; i<man.size(); i++)
            drawCar(man.getCar(i), i*15, window);
        window.display();
    }
}