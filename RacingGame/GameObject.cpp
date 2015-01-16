//
//  GameObject.cpp
//  SFML Test
//
//  Created by James Lennon on 11/7/14.
//  Copyright (c) 2014 James Lennon. All rights reserved.
//

#include "GameObject.h"

void GameObject::update(float dt){}

void GameObject::draw(sf::RenderWindow &window){
    window.draw(_img);
}

void GameObject::setPosition(float x, float y){
    _img.setPosition(x, y);
}

void GameObject::setManager(GameObjectManager *manager){
    _manager = manager;
}

void GameObject::remove(){
    if(_manager!=nullptr)_manager->remove(this);
}

float GameObject::x(){
    return (left()+right())/2;
}

float GameObject::y(){
    return (top()+bottom())/2;
}

float GameObject::top(){
    return _img.getGlobalBounds().top;
}

float GameObject::right(){
    return _img.getGlobalBounds().left + _img.getGlobalBounds().width;
}

float GameObject::bottom(){
    return _img.getGlobalBounds().top + _img.getGlobalBounds().height;
}

float GameObject::left(){
    return _img.getGlobalBounds().left;
}

Rect<float> GameObject::getBounds(){
    return _img.getGlobalBounds();
}

bool GameObject::intersects(GameObject &other){
    return getBounds().intersects(other.getBounds());
}

void GameObject::setDir(GameObject::Direction dir){
    switch (dir) {
        case Up:
            _dx = 0;
            _dy = -1;
            break;
        case Right:
            _dx = 1;
            _dy = 0;
            break;
        case Down:
            _dx = 0;
            _dy = 1;
            break;
        case Left:
            _dx = -1;
            _dy = 0;
            break;
        case None:
            _dx = _dy = 0;
            break;
    }
}

void GameObject::onRemove(){}

GameObjectManager::GameObjectManager(){
}

void GameObjectManager::add(GameObject *obj){
    obj->setManager(this);
    _objects.emplace_back(obj);
}

void GameObjectManager::remove(GameObject *obj){
    vector<GameObject*>::iterator it = find(_objects.begin(), _objects.end(), obj);
    if(it!=_objects.end()){
        _objects.erase(it);
    }
}


void GameObjectManager::updateAndRender(RenderWindow& window){
    float dt = _clock.restart().asSeconds();
    for (int i=0; i<_objects.size(); i++) {
        _objects[i]->update(dt);
    }
    for (int i=0; i<_objects.size(); i++) {
        _objects[i]->draw(window);
    }
}

TextObject::TextObject(string text, Font font, int size, Color col){
    _font = font;
    _text.setFont(_font);
    _text.setString(text);
    _text.setCharacterSize(size);
    _text.setColor(col);
}

void TextObject::setText(string text){
    _text.setString(text);
}

void TextObject::setPosition(float x, float y){
    _text.setPosition(x, y);
}

void TextObject::draw(sf::RenderWindow &window){
    window.draw(_text);
}

Rect<float> TextObject::getBounds(){
    return _text.getGlobalBounds();
}
