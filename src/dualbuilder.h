

#ifndef DUALBUILDER_H
#define DUALBUILDER_H

#include "mapbuilder.h"
#include "standardfactory.h"
#include "easyfactory.h"

class DualBuilder: public MapBuilder
{
public:
    DualBuilder(int width, int height);
    void buildMap(ObjectFactory& factory);
    void buildBlock(ObjectFactory& factory, QWidget *game);
    void buildPlatform(ObjectFactory& factory);
    void buildBall(ObjectFactory& factory);
    Map* getMap();

protected:
    Map* m_currentMap;
    int m_width;
    int m_height;
};

#endif // DUALBUILDER_H
