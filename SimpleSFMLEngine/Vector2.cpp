#include "stdafx.h"
#include "Vector2.h"


Vector2::Vector2(float xorangle, float yormagnitude, bool fromAngleAndMag)
{
    if (!fromAngleAndMag)
    {
        x = xorangle;
        y = yormagnitude;
    }
    else
    {
        x = yormagnitude * cosf(xorangle);
        y = yormagnitude * sinf(xorangle);
    }
}

Vector2::Vector2(sf::Vector2f other)
{
    x = other.x;
    y = other.y;
}

Vector2 Vector2::operator*(float scalar) const
{
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const
{
    return Vector2(x / scalar, y / scalar);
}

Vector2 Vector2::operator*(const Vector2 & other) const
{
    return Vector2(x * other.x, y * other.y);
}

Vector2 Vector2::operator+(const Vector2 & other) const
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2 & other) const
{
    return Vector2(x - other.x, y - other.y);
}

void Vector2::rotate(float angle, const Vector2 & axis)
{
    *this -= axis;

    float xt = (x * cosf(angle)) - (y * sinf(angle));
    float yt = (x * sinf(angle)) + (y * cosf(angle));

    x = xt;
    y = yt;

    *this += axis;
}

float Vector2::angle(const Vector2 & other) const
{
    int sign = 1;
    if (y < other.y)
        sign = -1;
    
    return sign * acosf(dot(other) / (mag() * other.mag()));
}

float Vector2::mag() const
{
    return sqrt(mag2());
}

float Vector2::mag2() const
{
    return x * x + y * y;
}

void Vector2::normalize()
{
    *this = normalized();
}

Vector2 Vector2::normalized() const
{
    return *this / mag();
}

float Vector2::dot(const Vector2 & other) const
{
    return x * other.x + y * other.y;
}

void Vector2::lerp(const Vector2 & destination, float t)
{
    *this = Vector2::lerp(*this, destination, t);
}

Vector2 Vector2::lerp(const Vector2 & from, const Vector2 & to, float t)
{
    return from + (to - from) * t;
}
