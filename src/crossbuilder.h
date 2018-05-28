

#ifndef CROSSBUILDER_H
#define CROSSBUILDER_H

#include "mapbuilder.h"
#include "easyfactory.h"

class CrossBuilder: public MapBuilder
{
public:
    CrossBuilder(int width, int height);
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

#endif // CROSSBUILDER_H
