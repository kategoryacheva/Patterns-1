

#ifndef STATEBALLTOPCONTROL_H
#define STATEBALLTOPCONTROL_H

#include <QPainter>
#include "stateball.h"
#include "stateballbottomcontrol.h"

class Ball;

class StateBallTopControl: public StateBall
{
public:
    static StateBall* Instance();
    virtual void onCollision(Ball *o);
    virtual void accept(Ball *b,PaintVisitor& v);

private:
    StateBallTopControl();

private:
    static StateBallTopControl* m_stateInstance;
};

#endif // STATEBALLTOPCONTROL_H
