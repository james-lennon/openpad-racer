//
//  Game.h
//  SFML Test
//
//  Created by James Lennon on 11/6/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#ifndef __SFML_Test__Game__
#define __SFML_Test__Game__

#include "stdafx.h"
#include <map>
using namespace sf;
using namespace std;

class Screen {
    
public:
    virtual void show(RenderWindow & window);
};

class Game {
    
public:
    static void start(VideoMode bounds, string title, string iconPath="");
    static void gameLoop();
    static void addScreen(string name, Screen* screen);
    static void showScreen(string name);
    static string currentScreenName();
    static Screen* currentScreen();
    static void exit();
    static RenderWindow& getWindow();
    
private:
    static RenderWindow _window;
    static Screen *_curScreen;
    static string _curName;
    static map<string,Screen*> _screens;
    static bool _shouldExit;
};

#endif /* defined(__SFML_Test__Game__) */
