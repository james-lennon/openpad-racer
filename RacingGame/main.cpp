
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
#include "VisualizerScreen.h"
#include "LoadingScreen.h"
#include "RacerHandler.h"
#include "FinishedScreen.h"
#include <iostream>

using namespace std;

openpad::Server* serv;

void runServer(){
    RacerHandler handler;
    serv = new openpad::Server(handler);
    serv->start();
}

int main(int, char const**)
{
    Game::addScreen("track", new TrackScreen);
    Game::addScreen("visualizer", new VisualizerScreen);
    Game::addScreen("loading", new LoadingScreen);
    Game::addScreen("finished", new FinishedScreen);
    Game::showScreen("visualizer");
    
    Thread t(runServer);
    t.launch();
    
    Game::start(sf::VideoMode(800,600), "Openpad Racer", "");
    
    serv->stop();
    t.terminate();
    return 0;
}
