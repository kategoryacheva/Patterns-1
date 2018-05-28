#include "ball.h"
#include "paintvisitor.h"

Ball::Ball(StateBall *state) :
    MapObject(){
    m_currState = state;
}

Ball::Ball(float posX, float posY, StateBall *state) :
    MapObject(posX, posY), m_currState(state){
}

Ball::Ball(float posX, float posY, int radius, StateBall *state) :
    MapObject(posX, posY){
    m_radius = radius;
    m_currState = state;
}

void Ball::setPos(float posX, float posY){
    m_posX = posX;
    m_posY = posY;
}

void Ball::onCollision(int id){
    //id = -1 for all block that are non platform
    if((id != -1) && (id != m_lastPlatformCollided)){
        m_currState->onCollision(this);
        m_lastPlatformCollided = id;
    }
}

int Ball::getRadius(){
    return m_radius;
}

int Ball::getLastPlatformCollided(){
    return m_lastPlatformCollided;
}

void Ball::setLastPlatformCollided(int id){
    m_lastPlatformCollided = id;
}

void Ball::changeState(StateBall *newState){
    m_currState = newState;
}

void Ball::accept(PaintVisitor& v){
    m_currState->accept(this, v);
}
