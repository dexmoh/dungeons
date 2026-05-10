#pragma once

struct Vector2;

// A 2D vector using integer coordinates.
class Vector2i {
public:
    int x;
    int y;

    Vector2i();
    Vector2i(Vector2 vec);
    Vector2i(int x_val, int y_val);

    // Converts this vector into a raylib Vector2 which uses floats.
    Vector2 to_rl_vector() const;

};
