//
//  RacerHandler.cpp
//  Openpad Racer
//
//  Created by James Lennon on 1/18/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#include "RacerHandler.h"
#include "TrackScreen.h"
#include "VisualizerScreen.h"

map<string, string> RacerHandler::names;

void RacerHandler::onStart(){
    ids.clear();
    names.clear();
}

string RacerHandler::getName(){
    return "Openpad Racer";
}

string RacerHandler::getDesc(){
    return "Multiplayer Racing Game";
}

string RacerHandler::getIconFilePath(){
    return resourcePath() + "icon-small.png";
}

int RacerHandler::getFilledSlots(){
    return ids.size();
}

int RacerHandler::getOpenSlots(){
    if(Game::currentScreenName()=="track")return 0;
    return 4-ids.size();
}

void RacerHandler::onJoin(openpad::Client *cli){
    ids.push_back(cli->getID().phoneid);
    names[cli->getID().phoneid] = cli->getID().username;
    if(ids.size()==4){
        showTrack();
    }
}

void RacerHandler::showTrack(){
    Game::showScreen("loading");
    VisualizerScreen::showTrack = true;
}

PadConfig RacerHandler::getDefaultControls(){
    //    return PadConfig::joystickWithButtonsLayout();
    PadConfig conf;
    ButtonControl *b = new ButtonControl(.5,.5,.5,0, BUTTON_A);
    conf.addControl(b);
    return conf;
}

void RacerHandler::onDisconnect(openpad::Client *cli){
    names.erase(names.find(cli->getID().phoneid));
    ids.erase(find(ids.begin(), ids.end(), cli->getID().phoneid));
    if(Game::currentScreenName() == "track"){
        TrackScreen::disconnectCar(cli->getID().phoneid);
    }
}

void RacerHandler::onPadUpdate(openpad::Client *cli, openpad::PadUpdateObject update){
    if(Game::currentScreenName()=="track"){
        TrackScreen::handleInput(cli->getID().phoneid, update);
    }else if(Game::currentScreenName()=="visualizer"){
        if(ids[0] == cli->getID().phoneid && update.action == ACTION_DOWN && update.controlid == 0){
            showTrack();
        }
    }
}
