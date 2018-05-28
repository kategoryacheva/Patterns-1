

#ifndef STATEBALL_H
#define STATEBALL_H

#include <QDebug>

#ifdef _MSC_VER
typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;
#else
#include <stdint.h>
#endif

class Ball;
class PaintVisitor;

class StateBall : public QObject
{
public:
    StateBall();
    virtual void accept(Ball *b, PaintVisitor& v)=0;
    virtual void onCollision(Ball *o)=0;

protected:
    void changeState(Ball* b, StateBall* s);
};

#endif // STATEBALL_H
