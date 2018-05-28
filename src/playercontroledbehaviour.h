

#ifndef PLAYERCONTROLEDBEHAVIOUR_H
#define PLAYERCONTROLEDBEHAVIOUR_H

#include "pbehaviour.h"
#include "platform.h"

class PlayerControledBehaviour: public PBehaviour
{
public:
    PlayerControledBehaviour(PhysicSystem& engine, Map& map, int platformId);
    void movePlatform(int ballPosX, int ballPosY, QKeyEvent* e = NULL);
};

#endif // PLAYERCONTROLEDBEHAVIOUR_H
