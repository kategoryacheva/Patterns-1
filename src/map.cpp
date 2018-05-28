#include "map.h"

Map::Map(){}

Map::Map(PhysicSystem& engine) :
    m_topGamerPoints(0),m_bottomGamerPoints(0){
    m_engine = &engine;
}

void Map::addObject(MapObject *object, Body *body){
    m_objects.insert(object->getId(),object);
    m_engine->addBody(body);
}

void Map::removeObject(int id){
    //m_objects.remove(id);
    //m_engine->removeBody(id);
    //m_objects.value(id)->setForRemoval();
    //m_engine->getBody(id)->setForRemoval();
    if(isBall(id)){
        m_ballsList.removeAll(id);
    } else if(isBonus(id)){
        m_bonusList.removeAll(id);
    }
    m_engine->getBody(id)->disable();
    m_objects.value(id)->disable();
}

MapObject* Map::getObject(int id){
   return m_objects.value(id);
}

void Map::mapStart(int msecUpdate){
    m_engine->start(msecUpdate);
}

void Map::mapPause(){
    m_engine->stop();
}

void Map::setEngine(PhysicSystem &engine){
    m_engine = &engine;
}

QList<int> Map::getObjectsKeys(){
    return m_objects.keys();
}

void Map::setBottomPlatform(int id){
    m_bottomPlatformId = id;
}

void Map::setTopPlatform(int id){
    m_topPlatformId = id;
}

int Map::getBottomPlatform(){
    return m_bottomPlatformId;
}

int Map::getTopPlatform(){
    return m_topPlatformId;
}

bool Map::isBall(int id){
    return m_ballsList.contains(id);
}

bool Map::isBonus(int id){
    return m_bonusList.contains(id);
}

void Map::addBallToList(int id){
    m_ballsList.append(id);
}

void Map::addBonusToList(int id){
    m_bonusList.append(id);
}

void Map::removeballFromList(int id){
    m_ballsList.removeOne(id);
}

QHash<int,MapObject*>* Map::getObjects(){
    return &m_objects;
}

int Map::getGameFreeWidth(){
    return m_gameFreeWidth;
}

void Map::setGameFreeWidth(int width){
    m_gameFreeWidth = width;
}

int Map::getWidth(){
    return m_width;
}

int Map::getHeight(){
    return m_height;
}

void Map::setWidth(int width){
    m_width = width;
}

void Map::setTopWall(int id){
    m_topWall = id;
}

int Map::getTopWall(){
    return m_topWall;
}

void Map::setBottomWall(int id){
    m_bottomWall = id;
}

int Map::getBottomWall(){
    return m_bottomWall;
}

int Map::getBottomLifes(){
    return m_bottomLifes;
}

int Map::getTopLifes(){
    return  m_topLifes;
}

void Map::setBottomLifes(int lifes){
    m_bottomLifes = lifes;
}

void Map::setTopLifes(int lifes){
    m_topLifes = lifes;
}
