#include "physicsystem.h"
//#include <algorithm>
#include <stdio.h>
#include <cmath>

static const int coefVelTrans = 0.95;

PhysicSystem::PhysicSystem(){
    QObject::connect(&(this->m_timer), SIGNAL(timeout()), this, SLOT(updateWorld()));
}

void PhysicSystem::updateWorld(){
    QMutableHashIterator<int, Body*> i(*(listBodies()));

    while (i.hasNext()) {
        i.next();
        if(i.value()->isEnabled()){
            //signal if body has changed position
            if(i.value()->updateBody(0.0)){
                emit newPosition(i.value()->getId(), i.value()->getPosition().getX(), i.value()->getPosition().getY());
            }
            //if body is a circle check for collisions with other objects
            if(i.value()->getShapeType() == CIRCLE) {
                QHashIterator<int, Body*> j(*(listBodies()));
                while (j.hasNext()) {
                    j.next();
                    collSide collision = isColliding(i.value(), j.value());
                    //if there was a collision and it was not with another circle apply action
                    if(j.value()->getShapeType() != CIRCLE && collision != NOCOLL) {
                        actionCollision(i.value(), j.value(), collision);
                    }
                }
            }
        } else {
            i.remove();
        }
    }
}

void PhysicSystem::start(int msec){
    this->m_timer.start(msec);
}

void PhysicSystem::stop(){
    this->m_timer.stop();
}

void PhysicSystem::addBody(Body *body){
    this->m_bodies.insert(body->getId(),body);
}

void PhysicSystem::removeBody(int id){
    this->m_bodies.remove(id);
}

Body* PhysicSystem::getBody(int id){
    return this->m_bodies.value(id);
}

QHash<int, Body*>* PhysicSystem::listBodies(){
    return &m_bodies;
}

// Verifies if bodyA is colliding with bodyB
collSide PhysicSystem::isColliding(Body *bodyA, Body *bodyB){
    if((bodyA->getShapeType() == CIRCLE) && (bodyB->getShapeType() == RECTANGLE)){
        Circle* circle = static_cast<Circle*>(bodyA);
        Rectangle* rectangle = static_cast<Rectangle*>(bodyB);
        return intersect(circle, rectangle);
    } else if ((bodyA->getShapeType() == RECTANGLE) && (bodyB->getShapeType() == CIRCLE)){
        Circle* circle = static_cast<Circle*>(bodyB);
        Rectangle* rectangle = static_cast<Rectangle*>(bodyA);
        return intersect(circle, rectangle);
    }
    return NOCOLL;
}

// Verifies if circle intersects a rectangle
collSide PhysicSystem::intersect(Circle *circle, Rectangle *rect){
    float circlePosX = circle->getPosition().getX();
    float circlePosY = circle->getPosition().getY();
    float circleDistanceX = abs(circlePosX - rect->getPosition().getX());
    float circleDistanceY = abs(circlePosY - rect->getPosition().getY());

    if (circleDistanceX > (rect->getWidth()/2.0 + circle->getRadius())) { return NOCOLL; }
    if (circleDistanceY > (rect->getHeight()/2.0 + circle->getRadius())) { return NOCOLL; }

    if (circleDistanceX <= (rect->getWidth()/2.0)) { return TOPBOTTOM; }
    if (circleDistanceY <= (rect->getHeight()/2.0)) { return LEFTRIGHT; }

    float cornerDistance_sq = pow((circleDistanceX - rect->getWidth()/2.0),2.0) +
            pow((circleDistanceY - rect->getHeight()/2.0),2.0);

    if(cornerDistance_sq <= (pow(circle->getRadius(),2.0))){
        float rectSideLeft = rect->getPosition().getX() - rect->getWidth()/2.0;
        float rectSideRight = rect->getPosition().getX() + rect->getWidth()/2.0;
        float rectSideTop = rect->getPosition().getY() - rect->getHeight()/2.0;
        float rectSideBottom = rect->getPosition().getY() + rect->getHeight()/2.0;

        if(circlePosX < rectSideLeft) {
            return CORNERLEFT;
        } else if(circlePosX > rectSideRight) {
            return CORNERRIGHT;
        }
        //return CORNER;
    }
    return NOCOLL;
}

// Applies an action when bodyA collides with bodyB in side of bodyB
void PhysicSystem::actionCollision(Body *bodyA, Body *bodyB, collSide side){
    if(bodyA->getShapeType() == CIRCLE && bodyB->getShapeType() == RECTANGLE){
        Circle* circle = static_cast<Circle*>(bodyA);
        Rectangle* rect = static_cast<Rectangle*>(bodyB);
        float cpX = circle->getPosition().getX();
        float cpY = circle->getPosition().getY();
        float rpX = rect->getPosition().getX();
        float rpY = rect->getPosition().getY();
        float cvX = circle->getVelocity().getX();
        float cvY = circle->getVelocity().getY();
        float rvX = rect->getVelocity().getX();
        float rvY = rect->getVelocity().getY();

        Vector2D newVelocity(0.0, 0.0);
        switch(side) {
//        case CORNER:
//            newVelocity.setX(-cvX+rvX * coefVelTrans);
//            newVelocity.setY(-cvY+rvY);
//            circle->setVelocity(newVelocity);
//            break;
        case CORNERLEFT:
            if(cvX > 0){ //from outside
                newVelocity.setX(-cvX+rvX * coefVelTrans);
                newVelocity.setY(-cvY+rvY);
            } else { //from inside
                newVelocity.setX(cvX+rvX * coefVelTrans);
                newVelocity.setY(-cvY+rvY);
            }
            circle->setVelocity(newVelocity);
            break;
        case CORNERRIGHT:
            if(cvX < 0){ //from outside
             newVelocity.setX(-cvX+rvX * coefVelTrans);
             newVelocity.setY(-cvY+rvY);
            } else { //from inside
                newVelocity.setX(cvX+rvX * coefVelTrans);
                newVelocity.setY(-cvY+rvY);
            }
            circle->setVelocity(newVelocity);
            break;
        case TOPBOTTOM:
            if(cpY < rpY) {
                circle->setPosition(cpX, rpY - (circle->getRadius() + rect->getHeight() /2 + 1));
            } else {
                circle->setPosition(cpX, rpY + (circle->getRadius() + rect->getHeight() /2 + 1));
            }
            newVelocity.setX(cvX+rvX * coefVelTrans);
            newVelocity.setY(-cvY+rvY);
            circle->setVelocity(newVelocity);
            break;
        case LEFTRIGHT:
            if(cpX < rpX) {
                circle->setPosition(rpX - (circle->getRadius() + rect->getWidth() /2 + 1), cpY);
            } else {
                circle->setPosition(rpX + (circle->getRadius() + rect->getWidth() /2 + 1), cpY);
            }
            newVelocity.setX(-cvX+rvX * coefVelTrans);
            newVelocity.setY(cvY+rvY);
            circle->setVelocity(newVelocity);
            break;
        case NOCOLL:
            break;
        }
    //the first parameter must be the circle
    emit collision(circle->getId(), rect->getId());
    }
}

bool PhysicSystem::isempty(){
    return this->m_bodies.isEmpty();
}

void PhysicSystem::cleanBodies(){
    m_timer.stop();
//    QMutableHashIterator<int, Body*> i(*(listBodies()));

//    while (i.hasNext()) {
//        i.next();
//        i.remove();
//    }
}
