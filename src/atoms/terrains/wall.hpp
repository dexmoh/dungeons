#pragma once

#include "pch.hpp"
#include "atoms/terrains/terrain.hpp"

class Wall : public Terrain {
public:
    enum SpriteID : std::uint8_t {
        STONE_WALL_TILE = 0
    };

    Wall(Game& ctx);

};
