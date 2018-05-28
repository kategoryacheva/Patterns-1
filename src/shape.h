#ifndef SHAPE_H
#define SHAPE_H

#include "body.h"

class Shape: public Body{
public:
    shapeType getShapeType();
protected:
    Shape(Vector2D &position, shapeType shape, int id);
    ~Shape();
    shapeType m_shape;
};

class Circle: public Shape{
public:
    Circle(Vector2D &position, int id, int radius);
    ~Circle();
    int m_radius;
    int getRadius();
    void setRadius(int radius);
};

class Rectangle: public Shape{
public:
    Rectangle(Vector2D &position, int id, int width, int height);
    ~Rectangle();
    int m_width;
    int m_height;
    void setDimensions(int width, int height);
    int getHeight();
    int getWidth();
};


#endif // SHAPE_H
