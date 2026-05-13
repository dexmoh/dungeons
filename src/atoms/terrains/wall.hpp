#pragma once

#include "pch.hpp"
#include "atoms/terrains/terrain.hpp"

class Game;

class Wall : public Terrain {
public:
    void ready(Game* ctx) override;

};
