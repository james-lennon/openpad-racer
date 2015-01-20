//
//  VisualizerScreen.cpp
//  OpenpadRacer
//
//  Created by James Lennon on 1/17/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "VisualizerScreen.h"

bool VisualizerScreen::showTrack = false;

void VisualizerScreen::drawTrack(RenderWindow& window){
    int thickness = 60;
    for(int i=0; i<_gen->track_list.size(); i++){
        Vertex lis[] =
        {
            Vector2f(margin+_gen->track_list[i].first*scalex, margin+_gen->track_list[i].second*scaley),
            Vector2f(margin+_gen->track_list[(i+thickness)%_gen->track_list.size()].first*scalex, margin+_gen->track_list[(i+thickness)%_gen->track_list.size()].second*scaley)
        };
        lis[0].color = Color::Red;
        lis[1].color = Color::Blue;
        window.draw(lis, 2, PrimitiveType::LinesStrip);
    }
    
}

void VisualizerScreen::show(sf::RenderWindow &window){
    mapx = 200;
    mapy = 200;
    margin = 50;
    scalex = (window.getSize().x - margin)/mapx;
    scaley = (window.getSize().y - margin)/mapy;
    
    _gen = new Generator(mapx,mapy,6);
    _gen->generate();
    
    Clock time;
    
    Font sans;
    sans.loadFromFile(resourcePath()+"sansation.ttf");
    Text title("Openpad Racer", sans);
    title.setCharacterSize(70);
    title.setPosition(window.getSize().x/2-title.getLocalBounds().width/2, 200);
    
    
    while(window.isOpen()){
        sf::Event evt;
        while(window.pollEvent(evt)){
            if(evt.type == Event::Closed || (evt.type == Event::KeyPressed && evt.key.code == sf::Keyboard::Escape)){
                Game::exit();
            }else if(evt.type == Event::KeyPressed){
//                if(evt.key.code == Keyboard::Space){
//                    _gen->difficulty = 4 + rand()%4;
//                    _gen->generate();
//                }
            }
        }
        if(time.getElapsedTime().asSeconds()>3){
            _gen->difficulty = 4 + rand()%4;
            _gen->generate();
            time.restart();
        }
        if(showTrack)return;
        window.clear(Color::Black);
        drawTrack(window);
        window.draw(title);
        window.display();
    }
}