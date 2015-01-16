//
//  Game.cpp
//  SFML Test
//
//  Created by James Lennon on 11/6/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include "Game.h"

void Screen::show(sf::RenderWindow &window){}

RenderWindow Game::_window;
bool Game::_shouldExit = false;
Screen* Game::_curScreen = nullptr;
string Game::_curName;
map<string, Screen*> Game::_screens;

void Game::start(VideoMode bounds, string title, string iconPath){
    _shouldExit = false;
    _window.create(bounds, title);
    _window.setFramerateLimit(60);
    
    if(iconPath != ""){
        Image icon;
        icon.loadFromFile(iconPath);
        _window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    
    while (!_shouldExit) {
        gameLoop();
    }
}

void Game::gameLoop(){
    if(_curScreen!=nullptr)_curScreen->show(_window);
}

void Game::addScreen(string name, Screen *screen){
    _screens[name] = screen;
}

void Game::showScreen(string name){
    if(_screens.find(name)==_screens.end()){
        printf("Invalid screen name: %s\n", name.c_str());
        return;
    }
    _curName = name;
    _curScreen = _screens[name];
}

Screen* Game::currentScreen(){
    return _curScreen;
}

string Game::currentScreenName(){
    return _curName;
}

void Game::exit(){
    _shouldExit = true;
    _window.close();
}

RenderWindow& Game::getWindow(){
    return _window;
}