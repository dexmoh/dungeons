#pragma once

#include "pch.hpp"

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

    // Draw tile elements in correct order.
    void draw(float delta);

    Vector2i get_position() const;
    void set_position(Vector2i position);

};
