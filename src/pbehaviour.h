

#ifndef PBEHAVIOUR_H
#define PBEHAVIOUR_H

#include <QObject>
#include <QKeyEvent>
#include "physicsystem.h"
#include "map.h"

class PBehaviour: public QObject
{
    Q_OBJECT
public:
    PBehaviour(PhysicSystem& engine, Map& map, int platformId);
    virtual void movePlatform(int ballPosX, int ballPosY, QKeyEvent* e) = 0;

protected:
    PhysicSystem* m_engine;
    int m_platformId;
    Map* m_currentMap;

signals:
    void newPosition(int bodyAId, float posX, float posY);
};

#endif // PBEHAVIOUR_H
