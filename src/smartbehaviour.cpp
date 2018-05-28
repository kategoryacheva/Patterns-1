

#include "smartbehaviour.h"

static const int velPlatform = 3.5;
static const int distSensorBall = 150;

SmartBehaviour::SmartBehaviour(PhysicSystem& engine, Map& map, int platformId) :
    PBehaviour(engine, map, platformId){}

void SmartBehaviour::movePlatform(int ballPosX, int ballPosY, QKeyEvent* e){
    if(e == NULL){
        Platform *platform = static_cast<Platform*>(m_currentMap->getObject(m_platformId));
        float platPosX = platform->getPosX();
        float platPosY = platform->getPosY();

        if((ballPosY < (platPosY + distSensorBall)) && (ballPosY > platPosY)){
            if(platPosX > ballPosX) {
                Vector2D vel(-velPlatform, 0);
                m_engine->getBody(m_platformId)->setVelocity(vel);
            } else if(platPosX < ballPosX) {
                Vector2D vel(velPlatform, 0);
                m_engine->getBody(m_platformId)->setVelocity(vel);
            }
        } else {
            Vector2D velNull(0, 0);
            m_engine->getBody(m_platformId)->setVelocity(velNull);
        }
    }
}

