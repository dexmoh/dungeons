#pragma once

#include "pch.hpp"

class Level;
class Atom;
class Terrain;
class Object;
class Mob;

// Container class for holding information about a tile in the level grid.
class Tile {
private:
    Vector2i _position = Vector2i::ZERO;

    Terrain* _terrain = nullptr;
    std::vector<Object*> _objects;
    std::vector<Mob*> _mobs;

private:
    Tile() = default;
    Tile(Vector2i position);

    bool _try_add(Atom* atom);
    bool _try_remove(Atom* atom);

public:
    // Check if the tile is solid.
    bool is_solid() const;

    // Check if the tile contains an atom.
    bool contains(Atom* atom) const;

    /* Getters */
    Vector2i get_position() const;
    Terrain* get_terrain();
    const std::vector<Object*>& get_objects() const;
    const std::vector<Mob*>& get_mobs() const;

    // Only Level is allowed to create tiles and add, or remove atoms from them.
    friend class Level;

};
