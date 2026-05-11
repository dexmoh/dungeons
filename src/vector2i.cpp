#include "vector2i.hpp"

#include "pch.hpp"

const Vector2i Vector2i::ZERO  = Vector2i(0, 0);
const Vector2i Vector2i::ONE   = Vector2i(1, 1);
const Vector2i Vector2i::UP    = Vector2i(0, 1);
const Vector2i Vector2i::DOWN  = Vector2i(0, -1);
const Vector2i Vector2i::LEFT  = Vector2i(-1, 0);
const Vector2i Vector2i::RIGHT = Vector2i(1, 0);

Vector2i::Vector2i()
    : x{ 0 }, y{ 0 }
{}

Vector2i::Vector2i(Vector2 vec)
    : x{ int(vec.x) }, y{ int(vec.y) }
{}

Vector2i::Vector2i(int x_val, int y_val)
    : x{ x_val }, y{ y_val }
{}

int Vector2i::width() const { return x; }
int Vector2i::height() const { return y; }

Vector2 Vector2i::to_rl_vector() const {
    return { float(x), float(y) };
}

/* Operator overloads. */
Vector2i Vector2i::operator+(const Vector2i& other) const {
    return Vector2i(x + other.x, y + other.y);
}

Vector2i& Vector2i::operator+=(const Vector2i& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2i Vector2i::operator-(const Vector2i& other) const {
    return Vector2i(x - other.x, y - other.y);
}

Vector2i& Vector2i::operator-=(const Vector2i& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2i Vector2i::operator*(const Vector2i& other) const {
    return Vector2i(x * other.x, y * other.y);
}

Vector2i& Vector2i::operator*=(const Vector2i& other) {
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector2i Vector2i::operator/(const Vector2i& other) const {
    return Vector2i(x / other.x, y / other.y);
}

Vector2i& Vector2i::operator/=(const Vector2i& other) {
    x /= other.x;
    y /= other.y;
    return *this;
}
