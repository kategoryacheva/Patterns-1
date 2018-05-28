

#ifndef STATEBLOCKINITIAL_H
#define STATEBLOCKINITIAL_H

#include <QPainter>
#include "stateblock.h"
#include "stateblockcollided.h"
#include "stateblockfinal.h"

class Block;

class StateBlockInitial: public StateBlock
{
public:
    static StateBlock* Instance();
    virtual void onCollision(Block *o);
    virtual void accept(Block *b,PaintVisitor& v);

private:
    StateBlockInitial();

private:
    static StateBlockInitial* m_stateInstance;
};

#endif // STATEBLOCKINITIAL_H
