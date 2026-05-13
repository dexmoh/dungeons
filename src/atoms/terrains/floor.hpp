#pragma once

#include "pch.hpp"
#include "atoms/terrains/terrain.hpp"

class Game;

class Floor : public Terrain {
public:
    Floor();

    void ready(Game* ctx) override;

};
