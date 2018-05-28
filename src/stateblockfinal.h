

#ifndef STATEBLOCKFINAL_H
#define STATEBLOCKFINAL_H

#include <QPainter>
#include "stateblock.h"
#include "stateblockcollided.h"
#include "stateblockinitial.h"

class Block;

class StateBlockFinal: public StateBlock
{
public:
    static StateBlock* Instance();
    virtual void onCollision(Block *b);
    virtual void accept(Block *b,PaintVisitor& v);

private:
    StateBlockFinal();
    static StateBlockFinal* m_stateInstance;
};

#endif // STATEBLOCKFINAL_H
