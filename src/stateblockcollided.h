

#ifndef STATEBLOCKCOLLIDED_H
#define STATEBLOCKCOLLIDED_H

#include <QPainter>
#include "stateblock.h"
#include "stateblockfinal.h"
#include "paintvisitor.h"

class Block;

class StateBlockCollided: public StateBlock
{
public:
    static StateBlock* Instance();
    virtual void onCollision(Block *b);
    virtual void accept(Block *b,PaintVisitor& v);

private:
    StateBlockCollided();
    static StateBlockCollided* m_stateInstance;
};

#endif // STATEBLOCKCOLLIDED_H
