#include "util/vector2i.hpp"

#include "pch.hpp"

const Vector2i Vector2i::ZERO       = Vector2i( 0,  0 );
const Vector2i Vector2i::ONE        = Vector2i( 1,  1 );
const Vector2i Vector2i::UP         = Vector2i( 0,  1 );
const Vector2i Vector2i::DOWN       = Vector2i( 0, -1 );
const Vector2i Vector2i::LEFT       = Vector2i(-1,  0 );
const Vector2i Vector2i::RIGHT      = Vector2i( 1,  0 );
const Vector2i Vector2i::UP_LEFT    = Vector2i(-1,  1 );
const Vector2i Vector2i::UP_RIGHT   = Vector2i( 1,  1 );
const Vector2i Vector2i::DOWN_LEFT  = Vector2i(-1, -1 );
const Vector2i Vector2i::DOWN_RIGHT = Vector2i( 1, -1 );

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

Vector2i Vector2i::abs() const {
    return Vector2i(
        (x < 0) ? -x : x,
        (y < 0) ? -y : y
    );
}

double Vector2i::length() const {
    return std::sqrt(length_sq());
}

double Vector2i::length_sq() const {
    return double(x) * double(x) + double(y) * double(y);
}

bool Vector2i::is_zero() const {
    if (x == 0 && y == 0)
        return true;
    else
        return false;
}

bool Vector2i::is_one() const {
    if (x == 1 && y == 1)
        return true;
    else
        return false;
}

Vector2 Vector2i::to_rl_vector() const {
    return { float(x), float(y) };
}

Vector2i Vector2i::move_dir_to_vec(MoveDir dir) {
    switch (dir) {
        case MoveDir::NONE:
            return Vector2i::ZERO;
        case MoveDir::UP:
            return Vector2i::UP;
        case MoveDir::DOWN:
            return Vector2i::DOWN;
        case MoveDir::LEFT:
            return Vector2i::LEFT;
        case MoveDir::RIGHT:
            return Vector2i::RIGHT;
        case MoveDir::UP_LEFT:
            return Vector2i::UP_LEFT;
        case MoveDir::UP_RIGHT:
            return Vector2i::UP_RIGHT;
        case MoveDir::DOWN_LEFT:
            return Vector2i::DOWN_LEFT;
        case MoveDir::DOWN_RIGHT:
            return Vector2i::DOWN_RIGHT;
        default:
            return Vector2i::ZERO;
    }
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
