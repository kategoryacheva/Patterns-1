#ifndef MAP_H
#define MAP_H

#include <QHash>

#include"mapobject.h"
#include"physicsystem.h"
#ifdef _MSC_VER
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

class Map: public QObject
{
    Q_OBJECT
public:
    Map();
    Map(PhysicSystem& engine);
    void addObject(MapObject *object, Body *body);
    void setEngine(PhysicSystem& engine);
    void mapUpdate();
    MapObject* getObject(int id);
    QHash<int,MapObject*>* getObjects();
    QList<int> getObjectsKeys();
    void setBottomPlatform(int id);
    void setTopPlatform(int id);
    int getBottomPlatform();
    int getTopPlatform();
    bool isBall(int id);
    bool isBonus(int id);
    void addBallToList(int id);
    void addBonusToList(int id);
    void removeballFromList(int id);
    int getGameFreeWidth();
    void setGameFreeWidth(int width);
    void setWidth(int width);
    void setTopWall(int id);
    int getTopWall();
    void setBottomWall(int id);
    int getBottomWall();
    int getWidth();
    int getHeight();
    int getBottomLifes();
    int getTopLifes();
    void setBottomLifes(int lifes);
    void setTopLifes(int lifes);

public slots:
    void mapPause();
    void mapStart(int msecUpdate = 11);
    void removeObject(int blockId);

private:
    QHash<int,MapObject*> m_objects;
    PhysicSystem* m_engine;
    int m_bottomPlatformId;
    int m_topPlatformId;
    int m_bottomWall;
    int m_topWall;
    QList<int> m_ballsList;
    QList<int> m_bonusList;
    int m_topGamerPoints;
    int m_bottomGamerPoints;
    int m_gameFreeWidth;
    int m_width;
    int m_height;
    int m_bottomLifes;
    int m_topLifes;
};

#endif // MAP_H
