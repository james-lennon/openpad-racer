
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

// Here is a small helper for you ! Have a look.
#include "stdafx.h"
#include "TrackScreen.h"
#include "openpad.h"
#include <iostream>

using namespace std;

openpad::Server* serv;

void runServer(){
    openpad::ServerHandler handler;
    serv = new openpad::Server(handler);
    cout << "starting" << endl;
    serv->start();
    cout << "stopping" << endl;
}

int main(int, char const**)
{
    Game::addScreen("track", new TrackScreen);
    Game::showScreen("track");
    
    Thread t(runServer);
    t.launch();
    
    Game::start(sf::VideoMode(800,600), "Openpad Racer", "");
    
    serv->stop();
    int b = 5;
    return 0;
}
