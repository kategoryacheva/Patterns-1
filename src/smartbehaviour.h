

#ifndef SMARTBEHAVIOUR_H
#define SMARTBEHAVIOUR_H

#include "pbehaviour.h"
#include "platform.h"

class SmartBehaviour : public PBehaviour
{
public:
    SmartBehaviour(PhysicSystem& engine, Map& map, int platformId);
    void movePlatform(int ballPosX, int ballPosY, QKeyEvent* e = NULL);
};

#endif // SMARTBEHAVIOUR_H
