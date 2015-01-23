//
//  LoadingScreen.cpp
//  Openpad Racer
//
//  Created by James Lennon on 1/20/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "LoadingScreen.h"
#include "RacerHandler.h"
#include "TrackScreen.h"

void LoadingScreen::loadPlayers(){
    sans.loadFromFile(resourcePath()+"sansation.ttf");
    int i=0;
    for(map<string,string>::iterator it = RacerHandler::names.begin(); it!=RacerHandler::names.end(); ++it){
        struct player p;
        p.name.setFont(sans);
        p.name.setString(it->second);
        p.name.setCharacterSize(24);
        p.name.setColor(TrackScreen::color_list[i]);
        p.name.setPosition(Game::getWindow().getSize().x/2-p.name.getLocalBounds().width/2, 300 + (p.name.getLocalBounds().height+20)*i);
        
        players.push_back(p);
        i++;
    }
}

void LoadingScreen::show(sf::RenderWindow &window){
    time.restart();
    loadPlayers();
    countdown.setFont(sans);
    countdown.setCharacterSize(70);
    
    while (window.isOpen()) {
        Event evt;
        while (window.pollEvent(evt)) {
            if(evt.type == Event::Closed || (evt.type==Event::KeyPressed && evt.key.code == Keyboard::Escape)){
                Game::exit();
            }
        }
        if(time.getElapsedTime().asSeconds()>5){
            Game::showScreen("track");
            break;
        }
        window.clear(Color::Black);
        string s;
        int t = 5-(int)time.getElapsedTime().asSeconds();
        s += (t+'0');
        countdown.setString(s);
        countdown.setPosition(window.getSize().x/2-countdown.getLocalBounds().width/2, 100);
        window.draw(countdown);
        for(int i=0; i<players.size(); i++){
            window.draw(players[i].name);
        }
        
        window.display();
    }
}