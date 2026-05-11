#pragma once

struct Vector2;

// A 2D vector using integer coordinates.
class Vector2i {
public:
    int x;
    int y;

    static const Vector2i UP;
    static const Vector2i DOWN;
    static const Vector2i LEFT;
    static const Vector2i RIGHT;

    Vector2i();
    Vector2i(Vector2 vec);
    Vector2i(int x_val, int y_val);

    // Converts this vector into a raylib Vector2 which uses floats.
    Vector2 to_rl_vector() const;

    /* Operator overloads. */
    // Add two vectors together.
    Vector2i operator+(const Vector2i& other) const;
    Vector2i& operator+=(const Vector2i& other);

    // Subtract two vectors.
    Vector2i operator-(const Vector2i& other) const;
    Vector2i& operator-=(const Vector2i& other);

    // Multiply two vectors.
    Vector2i operator*(const Vector2i& other) const;
    Vector2i& operator*=(const Vector2i& other);

    // Divide two vectors.
    Vector2i operator/(const Vector2i& other) const;
    Vector2i& operator/=(const Vector2i& other);

};
