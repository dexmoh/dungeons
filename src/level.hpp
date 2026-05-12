#pragma once

#include "pch.hpp"

class Game;
class Tile;

class Level {
private:
    Vector2i _size;
    Tile* _tiles;

public:
    Color clear_color;
    static constexpr Color DEFAULT_CLEAR_COLOR = (Color) { 5, 18, 18, 255 };

public:
    Level(Vector2i size);
    ~Level();

    void ready(Game* ctx); // Forwards a ready call to all atoms in the level. Called only once.
    void tick();           // Forwards a tick call to all atoms in the level. Called every tick.
    void draw() const;     // Forwards draw calls to all atoms in the level in correct order. Called every frame.

    Tile* get_tile(Vector2i position) const;

    // Generate a placeholder level for testing.
    static std::unique_ptr<Level> generate_placeholder();

};
