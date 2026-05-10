#pragma once

#include "pch.hpp"

class Tile;

class Level {
private:
    Vector2i _size;
    Tile* _tiles;

public:
    Level(Vector2i size);
    ~Level();

    // Draw tiles to the screen.
    void draw(float delta);

    Tile* get_tile(Vector2i position) const;

    // Generate a placeholder level for testing.
    static std::unique_ptr<Level> generate_placeholder();

};
