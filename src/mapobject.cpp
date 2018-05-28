

#include "mapobject.h"
#include "idgenerator.h"

MapObject::MapObject() :
    m_remove(false), m_points(0), m_enabled(true){
    this->id=IDGenerator::instance()->next();
}

MapObject::MapObject(float posX, float posY) :
    m_remove(false), m_points(0), m_enabled(true){
    this->id=IDGenerator::instance()->next();
    m_posX = posX;
    m_posY = posY;
}

int MapObject::getId(){
    return this->id;
}

float MapObject::getPosX(){
    return m_posX;
}

float MapObject::getPosY(){
    return m_posY;
}

void MapObject::emitObjectRemoval(int id){
    emit objectForRemoval(id);
}

bool MapObject::forRemoval(){
    return m_remove;
}

void MapObject::setForRemoval(){
    m_remove = true;
}

void MapObject::setPoints(int points){
    m_points = points;
}

int MapObject::getPoints(){
    return m_points;
}

bool MapObject::isEnabled(){
    return m_enabled;
}

void MapObject::disable(){
    m_enabled = false;
}

void MapObject::enable(){
    m_enabled = true;
}


