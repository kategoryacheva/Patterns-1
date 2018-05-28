

#ifndef MAPBUILDER_H
#define MAPBUILDER_H

#include "map.h"
#include "block.h"
#include "ball.h"
#include "platform.h"
#include "shape.h"
#include "objectfactory.h"
#include <QObject>

class MapBuilder: public QObject
{
    Q_OBJECT
public:
    virtual void buildMap(ObjectFactory& factory) = 0;
    virtual void buildBlock(ObjectFactory& factory, QWidget *game) = 0;
    virtual void buildPlatform(ObjectFactory& factory) = 0;
    virtual void buildBall(ObjectFactory& factory) = 0;
    virtual Map* getMap() = 0;

protected:
    MapBuilder();
};

#endif // MAPBUILDER_H
