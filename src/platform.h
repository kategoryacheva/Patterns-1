

#ifndef PLATFORM_H
#define PLATFORM_H

#include <QPainter>
#include "pbehaviour.h"
#include "mapobject.h"

class PaintVisitor;

class Platform : public MapObject
{
    Q_OBJECT

public:
    Platform();
    Platform(int width, int height);
    Platform(float posX, float posY, int width, int height);
    void setBehaviour(PBehaviour *behaviour);
    PBehaviour* getBehaviour();
    void move();
    void move(int ballPosX, int ballPosY, QKeyEvent* e);
    int getWidth();
    int getHeight();
    virtual void accept(PaintVisitor& v);
    void onCollision(int id);
    void setPos(float posX, float posY);

private:
    PBehaviour *behaviour;
    int m_height;
    int m_width;
};

#endif // PLATFORM_H
