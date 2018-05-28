

#ifndef STATEBALLBOTTOMCONTROL_H
#define STATEBALLBOTTOMCONTROL_H

#include <QPainter>
#include "stateball.h"
#include "stateballtopcontrol.h"
#include "paintvisitor.h"

class Ball;

class StateBallBottomControl: public StateBall
{
public:
    static StateBall* Instance();
    virtual void onCollision(Ball *o);
    virtual void accept(Ball *b,PaintVisitor& v);

private:
    StateBallBottomControl();

private:
    static StateBallBottomControl* m_stateInstance;
};

#endif // STATEBALLBOTTOMCONTROL_H
