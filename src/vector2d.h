#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
    Vector2D(float x=0.0, float y=0.0);
    float getX();
    float getY();
    void setX(float x);
    void setY(float y);
    Vector2D& operator=(const Vector2D &v);
    bool operator==(const Vector2D &v) const;
    Vector2D& operator+=(const Vector2D &v);
    Vector2D& operator -=(const Vector2D &v);
    Vector2D& operator/(float f) const;
    Vector2D& operator*(float f) const;
    float dot(const Vector2D &v);
    Vector2D& turnleft(const Vector2D &v);
    Vector2D& turnRight(const Vector2D &v);

private:
    float x;
    float y;
};

#endif // VECTOR2D_H
