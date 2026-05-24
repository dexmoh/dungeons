#pragma once

#include "pch.hpp"
#include "atoms/terrains/terrain.hpp"

class Floor : public Terrain {
public:
    enum SpriteID : std::uint8_t {
        GRASS_FLOOR_TILE_1 = 0,
        GRASS_FLOOR_TILE_2 = 1,
        GRASS_FLOOR_TILE_3 = 2,
        DIRT_FLOOR_TILE_1 = 3,
        DIRT_FLOOR_TILE_2 = 4,
        DIRT_FLOOR_TILE_3 = 5
    };

    Floor(Game& ctx);

};
