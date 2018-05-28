#include"shape.h"

Shape::Shape(Vector2D &position, shapeType shape, int id):
    Body(position, id){
    m_shape = shape;
}

Shape::~Shape(){}

shapeType Shape::getShapeType(){
    return m_shape;
}

Circle::Circle(Vector2D &position,  int id, int radius) :
    Shape(position, CIRCLE, id){
    m_radius = radius;
}

Circle::~Circle(){}

int Circle::getRadius(){
    return this->m_radius;
}

void Circle::setRadius(int radius){
    this->m_radius = radius;
}

Rectangle::Rectangle(Vector2D &position,  int id, int width, int height) :
    Shape(position, RECTANGLE, id){
    m_width = width;
    m_height = height;
}

Rectangle::~Rectangle(){}

void Rectangle::setDimensions(int width, int height){
    m_width = width;
    m_height = height;
}

int Rectangle::getWidth(){
    return m_width;
}

int Rectangle::getHeight(){
    return m_height;
}
