#pragma once

#include <cstdint>

// Defines 8 movement directions used by mobs.
enum class MoveDir : std::uint8_t {
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
