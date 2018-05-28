

#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include "mapobject.h"
#include "physicsystem.h"
#include "map.h"

class CrazyBricks;

class ObjectFactory
{
public:
    ObjectFactory(PhysicSystem& engine, Map& map);
    virtual MapObject* createBlock(float posX, float posY,int width, int height) = 0;
    virtual MapObject* createBall(float posX, float posY, ballInit location) = 0;
    virtual MapObject* createWallBlock(float posX, float posY,int width, int height) = 0;
    virtual MapObject* createPlatform(float posX, float posY,int width, int height, int limitXLeft, int limitXRight) = 0;
    PhysicSystem* getEngine();
    virtual MapObject* createBonus(float posX, float posY, bonusType type, int bonusToPlatformId, CrazyBricks* game)=0;
    virtual PaintVisitor* createPaintVisitor(QWidget *widget)=0;
    virtual void createBackground(QWidget *widget)=0;
protected:
    PhysicSystem* m_engine;
    Map* m_map;
};

#endif // OBJECTFACTORY_H
