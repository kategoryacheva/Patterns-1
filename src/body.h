#ifndef BODY_H
#define BODY_H


#include<vector>
#include "vector2d.h"
#include<list>
//#include "shape.h"
#ifdef _MSC_VER

typedef __int32 int32_t;
typedef unsigned __int32 uint32_t;
typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

#else
#include <stdint.h>
#endif

using namespace std;

enum shapeType { CIRCLE, RECTANGLE };

class Body{
public:
    Body(int);
    Body(Vector2D &position, int);
    ~Body();
    int getId();
    void setVelocity(Vector2D &velocity);
    void setAcceleration(Vector2D &acceleration);
    void setPosition(Vector2D &position);
    void setPosition(float posX, float posY);
    Vector2D getVelocity();
    Vector2D getAcceleration();
    Vector2D getPosition();
    bool operator ==(Body &other);
    bool updateBody(float time);
    virtual shapeType getShapeType() = 0;
    bool forRemoval();
    void setForRemoval();
    bool isEnabled();
    void disable();
    void enable();
    void setXLimits(int limitLeft, int limitRight);

protected:
    int id;
    bool m_remove;
    Vector2D velocity;
    Vector2D acceleration;
    Vector2D position;
    bool m_enabled;
    int m_limitXLeft;
    int m_limitXRight;
};

#endif // BODY_H
