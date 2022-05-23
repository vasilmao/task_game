#include "Vector.hpp"

Vector2::Vector2(float x, float y): x(x), y(y) {}

Vector2::Vector2(const Vector2& other): x(other.x), y(other.y) {}

float Vector2::GetX() const {
    return x;
}

float Vector2::GetY() const {
    return y;
}

void Vector2::SetX(float new_x) {
    x = new_x;
}

void Vector2::SetY(float new_y) {
    y = new_y;
}

float Vector2::GetLength() const {
    return sqrt(x * x + y * y);
}

void Vector2::Normalize() {
    float length = GetLength();
    x /= length;
    y /= length;
}

Vector2& operator += (Vector2& v1, const Vector2& v2) {
    v1.x += v2.x;
    v1.y += v2.y;
    return v1;
}

Vector2& operator -= (Vector2& v1, const Vector2& v2) {
    v1.x -= v2.x;
    v1.y -= v2.y;
    return v1;
}

Vector2 operator + (const Vector2& v1, const Vector2& v2) {
    Vector2 result(v1);
    result += v2;
    return result;
}

Vector2 operator - (const Vector2& v1, const Vector2& v2) {
    Vector2 result(v1);
    result -= v2;
    return result;
}

Vector2& operator *= (Vector2& vector, const float coef) {
    vector.x *= coef;
    vector.y *= coef;
    return vector;
}

Vector2 operator * (const Vector2& vector, const float coef) {
    Vector2 result(vector);
    result *= coef;
    return result;
}

Vector2 operator * (const float coef, const Vector2& vector) {
    Vector2 result(vector);
    result *= coef;
    return result;
}

float operator * (const Vector2& v1, const Vector2& v2) {
    float result = v1.x * v2.x + v1.y * v2.y;
    return result;
}

float operator ^ (const Vector2& v1, const Vector2& v2) {
    float result = v1.x * v2.y - v1.y * v2.x;
    return result;
}

Vector2 Vector2::elByElMult(const Vector2& v2) const {
    return Vector2(x * v2.x, y * v2.y);
}

Vector2 Vector2::GetProjection(const Vector2& other) const {
    return (*this) * other / other.GetLength() * other * (1 / other.GetLength());
}

Vector2 Vector2::Rotate(const Vector2& center, float angle) {
    float angle_cos = cos(angle);
    float angle_sin = sin(angle);

    float dx = x - center.x;
    float dy = y - center.y;
    return Vector2{center.x + dx * angle_cos - dy * angle_sin, center.y + dx * angle_sin + dy * angle_cos};
}

float DistSquare(const Vector2& p1, const Vector2& p2) {
    return (p1.GetX() - p2.GetX()) * (p1.GetX() - p2.GetX()) + (p1.GetY() - p2.GetY()) * (p1.GetY() - p2.GetY());
}

float AngleCos(const Vector2& v1, const Vector2& v2) {
    return (v1 * v2) / v1.GetLength() / v2.GetLength();
}