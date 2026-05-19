#pragma once

struct Vector2;
enum class MoveDir : unsigned char;

// A 2D vector using integer coordinates.
class Vector2i {
public:
    int x; // The X component.
    int y; // The Y component.

    static const Vector2i ZERO;
    static const Vector2i ONE;
    static const Vector2i UP;
    static const Vector2i DOWN;
    static const Vector2i LEFT;
    static const Vector2i RIGHT;
    static const Vector2i UP_LEFT;
    static const Vector2i UP_RIGHT;
    static const Vector2i DOWN_LEFT;
    static const Vector2i DOWN_RIGHT;

    Vector2i();
    Vector2i(Vector2 vec);
    Vector2i(int x_val, int y_val);

    int width() const;  // Returns the X component.
    int height() const; // Returns the Y component.

    Vector2i abs() const;     // Returns absolute value of vector.
    double length() const;    // Returns length (magnitude) of a vector.
    double length_sq() const; // Returns length squared of a vector.
    bool is_zero() const;     // Returns true if both components are zero.
    bool is_one() const;      // Returns true if both components are one.

    // Converts this vector into a raylib Vector2 which uses floats.
    Vector2 to_rl_vector() const;

    // Convert a move direction to a Vector2i value.
    static Vector2i move_dir_to_vec(MoveDir dir);

    /* Operator overloads. */
    bool operator==(const Vector2i& other) const;
    bool operator!=(const Vector2i& other) const;

    Vector2i operator+(const Vector2i& other) const;
    Vector2i& operator+=(const Vector2i& other);

    Vector2i operator-(const Vector2i& other) const;
    Vector2i& operator-=(const Vector2i& other);

    Vector2i operator*(const Vector2i& other) const;
    Vector2i& operator*=(const Vector2i& other);

    Vector2i operator/(const Vector2i& other) const;
    Vector2i& operator/=(const Vector2i& other);

};
