//
//  GameObject.h
//  SFML Test
//
//  Created by James Lennon on 11/7/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#ifndef __SFML_Test__GameObject__
#define __SFML_Test__GameObject__

#include <stdio.h>
#include "stdafx.h"

using namespace sf;
using namespace std;

class GameObjectManager;

class GameObject {
    
public:
    virtual void update(float dt);
    virtual void draw(RenderWindow& window);
    virtual void setPosition(float x, float y);
    virtual void setManager(GameObjectManager* manager);
    virtual void onRemove();
    void remove();
    Rect<float> getBounds();
    float x();
    float y();
    float top();
    float right();
    float bottom();
    float left();
    bool intersects(GameObject& other);
    
    enum Direction{
        Up,Down,Left,Right,None
    };
    void setDir(Direction dir);
    
protected:
    Sprite _img;
    Texture _tex;
    float _dx, _dy;
    GameObjectManager* _manager;
};

class TextObject: public GameObject{
public:
    TextObject(string text, Font font, int size=24, Color col=Color::White);
    
    virtual void draw(sf::RenderWindow &window);
    virtual void setPosition(float x, float y);
    virtual void setText(string text);
    virtual Rect<float> getBounds();
protected:
    Font _font;
    Text _text;
};

class GameObjectManager {
    
public:
    GameObjectManager();
    void add(GameObject* obj);
    void remove(GameObject* obj);
    void updateAndRender(RenderWindow& window);
    
private:
    vector<GameObject*> _objects;
    Clock _clock;
};

#endif /* defined(__SFML_Test__GameObject__) */
