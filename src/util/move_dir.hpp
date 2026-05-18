#pragma once

// Defines 8 movement directions used by mobs.
enum class MoveDir : unsigned char {
    NONE = 0,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};
