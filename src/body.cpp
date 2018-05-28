#include "body.h"
#include <stdio.h>

Body::Body(int id) :
    m_remove(false), m_enabled(true), m_limitXLeft(-1), m_limitXRight(-1){
    this->id=id;
}

Body::Body(Vector2D &position, int id) :
    m_remove(false), m_enabled(true), m_limitXLeft(-1), m_limitXRight(-1){
    this->id=id;
    this->position=position;
}

int Body::getId(){
    return this->id;
}

void Body::setVelocity(Vector2D &velocity){
    this->velocity=velocity;
}

void Body::setAcceleration(Vector2D &acceleration){
    this->acceleration=acceleration;
}

void Body::setPosition(Vector2D &position){
    this->position=position;
}

void Body::setPosition(float posX, float posY){
    Vector2D newPosition(posX, posY);
    this->position=newPosition;
}

Vector2D Body::getVelocity(){
    return this->velocity;
}

Vector2D Body::getAcceleration(){
    return this->acceleration;
}

Vector2D Body::getPosition(){
    return this->position;
}

bool Body::operator==(Body &other){
    return other.getId()==this->id;
}

bool Body::updateBody(float time){
    this->velocity+=this->acceleration;
    Vector2D newPos = this->position;
    newPos+=this->velocity;
    //dont let body move beyhond defined limit
    if(m_limitXLeft != -1 && (newPos.getX() < m_limitXLeft || newPos.getX() > m_limitXRight)){
        Vector2D zero(0, 0);
        this->velocity = zero;
        this->acceleration = zero;
        //return true if body changed from previous position
    } else if(!(this->position == newPos)) {
        this->position=newPos;
        return true;
    }
    return false;
}

bool Body::forRemoval(){
    return m_remove;
}

void Body::setForRemoval(){
    m_remove = true;
}

bool Body::isEnabled(){
    return m_enabled;
}

void Body::disable(){
    m_enabled = false;
}

void Body::enable(){
    m_enabled = true;
}

//if limitX= -1 means it has no limit, this is here mainly for platform limits
void Body::setXLimits(int limitLeft, int limitRight){
    m_limitXRight = limitRight;
    m_limitXLeft = limitLeft;
}


Body::~Body(){}
