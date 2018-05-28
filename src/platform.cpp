

#include "platform.h"
#include "paintvisitor.h"

Platform::Platform():
    MapObject(){}

Platform::Platform(int width, int height):
    MapObject(){
    m_width = width;
    m_height = height;
}

Platform::Platform(float posX, float posY, int width, int height):
    MapObject(posX, posY){
    m_width = width;
    m_height = height;
}

void Platform::setPos(float posX, float posY){
    m_posX = posX;
    m_posY = posY;
}

void Platform::setBehaviour(PBehaviour *behaviour){
    this->behaviour = behaviour;
}

PBehaviour* Platform::getBehaviour() {
    return this->behaviour;
}

void Platform::move(int ballPosX, int ballPosY, QKeyEvent* e){
    this->behaviour->movePlatform(ballPosX, ballPosY, e);
}

void Platform::onCollision(int id){
}

int Platform::getWidth(){
    return m_width;
}

int Platform::getHeight(){
    return m_height;
}

void Platform::accept(PaintVisitor& v){
    v.VisitPlatform(this);
}
