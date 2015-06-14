#pragma once
class Vector2 :
    public sf::Vector2f
{
public:
    Vector2(float xorangle = 0, float yormagnitude = 0, bool fromAngleAndMag = false);
    Vector2(sf::Vector2f other);

    Vector2 operator*(float scalar) const;
    Vector2 operator/(float scalar) const;
    Vector2 operator*(const Vector2& other) const;
    Vector2 operator+(const Vector2& other) const;
    Vector2 operator-(const Vector2& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector2& vector)
    {
        os << "(" << vector.x << ", " << vector.y << ")";
        return os;
    }

    void rotate(float angle, const Vector2& axis = Vector2(0, 0));
    float angle(const Vector2& other = Vector2(1, 0)) const;

    float mag() const;
    float mag2() const;

    void normalize();
    Vector2 normalized() const;

    float dot(const Vector2& other) const;

    void lerp(const Vector2& destination, float t);
    static Vector2 lerp(const Vector2& from, const Vector2& to, float t);
};

inline Vector2 operator*(float left, const Vector2& right)
{
    return{ left * right.x, left * right.y };
}

inline Vector2 operator-(const Vector2& right)
{
    return { -right.x, -right.y };
}