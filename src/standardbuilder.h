

#ifndef STANDARDBUILDER_H
#define STANDARDBUILDER_H

#include "mapbuilder.h"
#include "standardfactory.h"
#include "easyfactory.h"

class StandardBuilder: public MapBuilder
{
public:
    StandardBuilder(int width, int height);
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

#endif // STANDARDBUILDER_H
