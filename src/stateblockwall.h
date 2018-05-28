

#ifndef STATEBLOCKWALL_H
#define STATEBLOCKWALL_H

#include <QPainter>
#include "stateblock.h"
#include "stateblockcollided.h"
#include "stateblockfinal.h"

class Block;

class StateBlockWall: public StateBlock
{
public:
    static StateBlock* Instance();
    virtual void onCollision(Block *o);
    virtual void accept(Block *b,PaintVisitor& v);

private:
    StateBlockWall();

private:
    static StateBlockWall* m_stateInstance;
};

#endif // STATEBLOCKWALL_H
