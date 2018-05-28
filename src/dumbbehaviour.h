

#ifndef DUMBBEHAVIOUR_H
#define DUMBBEHAVIOUR_H

#include "pbehaviour.h"
#include "platform.h"

class DumbBehaviour : public PBehaviour
{
public:
    DumbBehaviour(PhysicSystem& engine, Map& map, int platformId);
    void movePlatform(int ballPosX, int ballPosY, QKeyEvent* e = NULL);
};

#endif // DUMBBEHAVIOUR_H
