

#include "dumbbehaviour.h"

static const int velPlatform = 3.5;
static const int distSensorBall = 150;

DumbBehaviour::DumbBehaviour(PhysicSystem& engine, Map& map, int platformId) :
    PBehaviour(engine, map, platformId){}

void DumbBehaviour::movePlatform(int ballPosX, int ballPosY, QKeyEvent* e){
    if(e == NULL){
           Platform *platform = static_cast<Platform*>(m_currentMap->getObject(m_platformId));
           float platPosX = platform->getPosX();
           float platPosY = platform->getPosY();
           int sideWallTickness = (m_currentMap->getWidth() - m_currentMap->getGameFreeWidth()) / 2;

           platPosX = ballPosX;
           if(platPosX - platform->getWidth() / 2 < sideWallTickness) {
               platPosX = sideWallTickness + platform->getWidth() / 2;
           } else if(platPosX + platform->getWidth() / 2 > (m_currentMap->getWidth() - sideWallTickness)) {
               platPosX = m_currentMap->getWidth() - sideWallTickness - platform->getWidth() / 2;
           }
           m_engine->getBody(m_platformId)->setPosition(platPosX, platPosY);
           emit newPosition(m_platformId, platPosX, platPosY);
    }
}

