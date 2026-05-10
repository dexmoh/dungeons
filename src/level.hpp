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

    // Forwards ready call to all level atoms.
    // Called once when the level has been loaded, before the game begins drawing.
    void ready(Game* ctx);

    // Draw tiles to the screen. Called every frame.
    void draw(float delta);

    Tile* get_tile(Vector2i position) const;

    // Generate a placeholder level for testing.
    static std::unique_ptr<Level> generate_placeholder();

};
