#pragma once

#include "Tools.hpp"

class Vector2 {

private:
    float x = 0;
    float y = 0;

public:
    Vector2(float x, float y);
    Vector2(const Vector2& other);

    Vector2(){}
    ~Vector2(){}

    float GetX() const;
    float GetY() const;
    void SetX(float new_x);
    void SetY(float new_y);
    float GetLength() const;
    void Normalize();
    Vector2 GetNormalized();

    friend bool operator == (const Vector2& v1, const Vector2& v2);
    friend bool operator != (const Vector2& v1, const Vector2& v2);
    friend Vector2 operator - (const Vector2& v);
    friend Vector2& operator += (Vector2& v1,     const Vector2& v2);
    friend Vector2& operator -= (Vector2& v1,     const Vector2& v2);
    friend Vector2 operator + (const Vector2& v1, const Vector2& v2);
    friend Vector2 operator - (const Vector2& v1, const Vector2& v2);
    friend Vector2& operator *= (Vector2& vector, const float coef);
    friend Vector2 operator * (const Vector2& vector, const float coef);
    friend Vector2 operator * (const float coef, const Vector2& vector);
    friend float operator * (const Vector2& v1, const Vector2& v2);
    friend float operator ^ (const Vector2& v1, const Vector2& v2);
    Vector2 elByElMult(const Vector2& v2) const;
    Vector2 GetProjection(const Vector2& other) const;
    Vector2 Rotate(const Vector2& other, float angle);
};

float Angle(const Vector2& v1, const Vector2& v2);
float AngleCos(const Vector2& v1, const Vector2& v2);

float DistSquare(const Vector2& p1, const Vector2& p2);