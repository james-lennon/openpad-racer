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
        Vertex lis[] = {Vector2f(track[i].first, track[i].second), Vector2f(track[(i+1)%track.size()].first,track[(i+1)%track.size()].second)};
        window.draw(lis, 2, PrimitiveType::Lines);
    }
}

void TrackScreen::show(sf::RenderWindow &window){
    _gen = new Generator(50,50,2);
    _gen->generate();
    
    while(window.isOpen()){
        sf::Event evt;
        while(window.pollEvent(evt)){
            if(evt.type == Event::Closed || (evt.type == Event::KeyPressed && evt.key.code == sf::Keyboard::Escape)){
                Game::exit();
            }else if(evt.type == Event::KeyPressed){
                
            }
        }
        
        window.clear(Color::Black);
        drawTrack(_gen->track_list, window);
        window.display();
    }
}