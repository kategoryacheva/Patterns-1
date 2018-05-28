#ifndef BALL_H
#define BALL_H

#include "mapobject.h"
#include "stateball.h"
#include <QPainter>

class PaintVisitor;

class Ball : public MapObject
{
    Q_OBJECT

    friend class StateBall;
    friend class StateBallGeneric;
    friend class StateBallTopControl;
    friend class StateBallBottomControl;

public:
    Ball(StateBall *state);
    Ball(float posX, float posY, StateBall *state);
    Ball(float posX, float posY, int radius, StateBall *state);
    void setPos(float posX, float posY);
    void onCollision(int id);
    int getLastPlatformCollided();
    void setLastPlatformCollided(int id);
    virtual void accept(PaintVisitor& v);
    int getRadius();

protected:
    void changeState(Ball* b, StateBall* s);

private:
    void changeState(StateBall *newState);

private:
    int m_radius;
    StateBall* m_currState;
    int m_lastPlatformCollided;
};

#endif // BALL_H
