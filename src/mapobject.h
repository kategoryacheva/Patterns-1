

#ifndef MAPOBJECT_H
#define MAPOBJECT_H

#include <QDebug>
#include <QWidget>

#ifdef _MSC_VER

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

#else
#include <stdint.h>
#endif

enum bonusType { NORMAL, WALLVISIBLE, WALLINVISIBLE, INDESTRUCTIBLE, BONUS1, BONUS2};
enum ballInit { BOTTOMBALL, TOPBALL };

class PaintVisitor;

class MapObject: public QObject
{
    Q_OBJECT

public:
    int getId();
    float getPosX();
    float getPosY();
    bool forRemoval();
    void emitObjectRemoval(int blockId);
    void setForRemoval();
    bool isEnabled();
    void disable();
    void enable();
    void setPoints(int points);
    int getPoints();
    //virtual ~MapObject();
    virtual void accept(PaintVisitor&) = 0;
    virtual void onCollision(int id) = 0;
    virtual void setPos(float posX, float posY) = 0;

protected:
    MapObject();
    MapObject(float posX, float posY);

signals:
    void objectForRemoval(int id);

protected:
    float m_posX;
    float m_posY;
    bool m_remove;
    bool m_enabled;

private:
    int id;
    int m_points;
};

#endif // MAPOBJECT_H
