//
//  FinishedScreen.cpp
//  Openpad Racer
//
//  Created by James Lennon on 1/22/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "FinishedScreen.h"
#include "car.h"

void FinishedScreen::show(sf::RenderWindow &window){
    Font sans;
    sans.loadFromFile(resourcePath()+"sansation.ttf");
    Text bigText("", sans);
    string msg;
    for(int i=0; i<CarManager::places.size(); i++){
        msg += i+'0';
        msg += "st: ";
        msg += CarManager::places[i];
        msg += "\n";
    }
    bigText.setString(msg);
    bigText.setPosition(window.getSize().x/2-bigText.getLocalBounds().width/2, window.getSize().y/2 - bigText.getLocalBounds().height/2);
    
    while (window.isOpen()) {
        Event evt;
        while (window.pollEvent(evt)) {
            if(evt.type==evt.Closed || (evt.type==Event::KeyPressed && evt.key.code==Keyboard::Escape)){
                Game::exit();
            }
        }
        
        window.clear();
        window.draw(bigText);
        window.display();
    }
}