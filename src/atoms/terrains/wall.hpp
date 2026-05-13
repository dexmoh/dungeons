#pragma once

#include "pch.hpp"
#include "atoms/terrains/terrain.hpp"

class Wall : public Terrain {
public:
    enum SpriteID {
        STONE_WALL_TILE = 0
    };

    Wall();

};
