#pragma once

#include "pch.hpp"

class Level;
class Terrain;
class Object;
class Mob;

// Container class for holding information about a tile in the level grid.
class Tile {
private:
    Vector2i _position;

    Terrain* _terrain;
    Object* _object;
    Mob* _mob;

    void _set_position(Vector2i position);
    void _set_terrain(Terrain* terrain);
    void _set_object(Object* object);
    void _set_mob(Mob* mob);

public:
    Tile();
    Tile(Vector2i position);

    bool is_solid() const;

    Vector2i get_position() const;
    Terrain* get_terrain();
    Object* get_object();
    Mob* get_mob();

    friend class Level;

};
