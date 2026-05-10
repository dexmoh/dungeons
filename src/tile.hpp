#pragma once

#include "pch.hpp"

class Game;
class Terrain;
class Object;
class Mob;
class Area;

// Represents a single tile in the level grid.
class Tile {
private:
    Vector2i _position;

    std::unique_ptr<Terrain> _terrain;
    std::vector<std::unique_ptr<Object>> _objects;
    std::unique_ptr<Mob> _mob;
    std::unique_ptr<Area> _area;

public:
    Tile();
    Tile(Vector2i position);
    ~Tile();

    // Forwards ready call to all atoms belonging to the tile.
    void ready(Game* ctx);

    // Draw tile elements in correct order.
    void draw(float delta);

    Vector2i get_position() const;

    void set_position(Vector2i position);
    void set_terrain(std::unique_ptr<Terrain> terrain);

};
