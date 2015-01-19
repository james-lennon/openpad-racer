//
//  RacerHandler.h
//  Openpad Racer
//
//  Created by James Lennon on 1/18/15.
//  Copyright (c) 2015 James Lennon. All rights reserved.
//

#ifndef __Openpad_Racer__RacerHandler__
#define __Openpad_Racer__RacerHandler__

#include "car.h"
#include <map>

using namespace openpad;
using namespace std;

class RacerHandler: public ServerHandler {
    vector<string> ids;
    map<string, string> names;
    
public:
    virtual void onStart();
    virtual string getName();
    virtual string getDesc();
    virtual string getIconFilePath();
    virtual int getFilledSlots();
    virtual int getOpenSlots();
    virtual void onJoin(Client* cli);
    virtual PadConfig getDefaultControls();
    virtual void onDisconnect(Client* cli);
    virtual void onPadUpdate(Client* cli, PadUpdateObject update);
    
private:
    void showTrack();
};

#endif /* defined(__Openpad_Racer__RacerHandler__) */
