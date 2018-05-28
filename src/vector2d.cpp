#include "vector2d.h"
#include <iostream>

using namespace std;

Vector2D::Vector2D(float x, float y){
    this->x=x;
    this->y=y;
}

float Vector2D::getX(){
    return this->x;
}

float Vector2D::getY(){
    return this->y;
}

void Vector2D::setX(float x){
    this->x=x;
}

void Vector2D::setY(float y){
    this->y=y;
}

float Vector2D::dot(const Vector2D &v){
    return x*v.x+y*v.y;
}

Vector2D& Vector2D::turnleft(const Vector2D &v){
    x=v.y;
    y=-v.x;
    return *this;
}

Vector2D& Vector2D::turnRight(const Vector2D &v){
    x=-v.y;
    y=v.x;
    return *this;
}

Vector2D& Vector2D::operator =(const Vector2D &v){
    x=v.x;
    y=v.y;
    return *this;
}

bool Vector2D::operator ==(const Vector2D &v) const{
    return (x==v.x && y==v.y);
}

Vector2D& Vector2D::operator +=(const Vector2D &v){
    x+=v.x;
    y+=v.y;
    return *this;
}

Vector2D& Vector2D::operator -=(const Vector2D &v){
    x-=v.x;
    y-=v.y;
    return *this;
}

Vector2D& Vector2D::operator *(const float f) const{
    Vector2D *temp=new Vector2D(x*f,y*f);
    return *temp;
}

Vector2D& Vector2D::operator /(const float f) const{
    Vector2D *temp=new Vector2D(x/f,y/f);
    return *temp;
}

