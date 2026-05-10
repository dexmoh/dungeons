#pragma once

#include "pch.hpp"

class Game;
class Tile;

class Level {
private:
    Vector2i _size;
    Tile* _tiles;

public:
    Level(Vector2i size);
    ~Level();

    // Forwards a ready call to all atoms in the level. Called only once.
    void ready(Game* ctx);

    // Forwards a tick call to all atoms in the level. Called every tick.
    void tick();

    // Forwards a draw call to all atoms in the level. Called every frame.
    void draw(float delta);

    Tile* get_tile(Vector2i position) const;

    // Generate a placeholder level for testing.
    static std::unique_ptr<Level> generate_placeholder();

};
