

#ifndef STATEBLOCK_H
#define STATEBLOCK_H

#include <QDebug>

#ifdef _MSC_VER
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

class Block;
class PaintVisitor;

class StateBlock : public QObject
{
public:
    StateBlock();
    virtual void onCollision(Block *o)=0;
    virtual void accept(Block *b,PaintVisitor& v)=0;

protected:
    void changeState(Block* b, StateBlock* s);
};

#endif // STATEBLOCK_H
