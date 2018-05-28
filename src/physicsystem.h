#ifndef PHYSICSYSTEM_H
#define PHYSICSYSTEM_H

#include<list>
#include"shape.h"
#include<stdio.h>
#include <QDebug>
#include <QObject>
#include <QTimer>

using namespace std;

enum collSide { TOPBOTTOM, LEFTRIGHT, CORNER, NOCOLL, CORNERLEFT, CORNERRIGHT };

class PhysicSystem: public QObject{
    Q_OBJECT
public:
    PhysicSystem();
    void addBody(Body *body);
    void removeBody(int id);
    QHash<int, Body*>* listBodies();
    Body* getBody(int id);
    collSide isColliding(Body *bodyA, Body *bodyB);
    void start(int time);
    void stop();
    bool isempty();
    void cleanBodies();

public slots:
    void updateWorld();

signals:
    void collision(int bodyAId, int bodyBId);
    void newPosition(int bodyAId, float posX, float posY);

private:
    float timeStep;
    QHash<int, Body*> m_bodies;
    collSide intersect(Circle *circle, Rectangle *rect);
    void actionCollision(Body *bodyA, Body *bodyB, collSide side);
    QTimer m_timer;
};

#endif // PHYSICSYSTEM_H
