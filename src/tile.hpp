#pragma once

#include "pch.hpp"

class Game;
class Terrain;
class Object;
class Mob;

// Container class for holding information about a tile in the level grid.
class Tile {
private:
    Vector2i _position;

    std::unique_ptr<Terrain> _terrain;
    std::vector<std::unique_ptr<Object>> _objects;
    std::unique_ptr<Mob> _mob;

public:
    Tile();
    Tile(Vector2i position);
    ~Tile();

    // Forwards a ready call to all atoms belonging to the tile. Called only once.
    void ready(Game* ctx);

    // Forwards a tick call to all atoms belonging to the tile. Called every tick.
    void tick();

    // Forwards a draw call to all atoms belonging to the tile. Called every frame.
    void draw(float delta);

    Vector2i get_position() const;

    void set_position(Vector2i position);
    void set_terrain(std::unique_ptr<Terrain> terrain);

};
