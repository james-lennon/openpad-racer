//
//  TrackScreen.cpp
//  RacingGame
//
//  Created by James Lennon on 1/15/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "TrackScreen.h"

void TrackScreen::drawTrack(vector<pair<int, int> > track, sf::RenderWindow &window){
    float scale = 40;
    for(int i=0; i<track.size(); i++){
        CircleShape dot;
        dot.setRadius(15);
        dot.setFillColor(Color::White);
        dot.setPosition(margin+track[i].first*scalex, margin+track[i].second*scaley);
        
        Vertex lis[] =
        {
            Vector2f(margin+track[i].first*scalex, margin+track[i].second*scaley),
            Vector2f(margin+track[(i+1)%track.size()].first*scalex, margin+track[(i+1)%track.size()].second*scaley)
        };
//        window.draw(lis, 2, PrimitiveType::Lines);
        window.draw(dot);
    }
}

void TrackScreen::show(sf::RenderWindow &window){
    mapx = 150;
    mapy = 150;
    margin = 50;
    scalex = (window.getSize().x - margin)/mapx;
    scaley = (window.getSize().y - margin)/mapy;
    
    _gen = new Generator(mapx,mapy,4);
    _gen->generate();
    
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
        drawTrack(_gen->track_list, window);
        window.display();
    }
}