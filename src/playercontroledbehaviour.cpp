

#include "playercontroledbehaviour.h"

static const int velPlatform = 5;

PlayerControledBehaviour::PlayerControledBehaviour(PhysicSystem& engine, Map& map,  int platformId) :
    PBehaviour(engine, map, platformId){}

void PlayerControledBehaviour::movePlatform(int ballPosX, int ballPosY, QKeyEvent* e){
    Vector2D velNull(0, 0);
    if(e != NULL && e->key()==Qt::Key_Left){
        if(e->type() == QEvent::KeyPress){
            Vector2D vel(- velPlatform, 0);
            m_engine->getBody(m_platformId)->setVelocity(vel);
        } else if(e->type() == QEvent::KeyRelease){
            Vector2D vel(0, 0);
            m_engine->getBody(m_platformId)->setVelocity(velNull);
        }
    }
    else if(e != NULL && e->key()==Qt::Key_Right){
        if(e->type() == QEvent::KeyPress){
            Vector2D vel(velPlatform, 0);
            m_engine->getBody(m_platformId)->setVelocity(vel);
        } else if(e->type() == QEvent::KeyRelease){
            Vector2D vel(0, 0);
            m_engine->getBody(m_platformId)->setVelocity(vel);
        }
    }
}

