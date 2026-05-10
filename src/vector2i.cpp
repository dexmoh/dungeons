#include "vector2i.hpp"

#include "pch.hpp"

Vector2i::Vector2i()
    : x{ 0 }, y{ 0 }
{}

Vector2i::Vector2i(Vector2 vec)
    : x{ int(vec.x) }, y{ int(vec.y) }
{}

Vector2i::Vector2i(int x_val, int y_val)
    : x{ x_val }, y{ y_val }
{}

Vector2 Vector2i::to_rl_vector() const {
    return { float(x), float(y) };
}
