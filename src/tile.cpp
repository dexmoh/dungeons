#include "tile.hpp"

#include "atoms/terrains/terrain.hpp"
#include "atoms/objects/object.hpp"
#include "atoms/mobs/mob.hpp"

Tile::Tile()
    : Tile(Vector2i::ZERO)
{}

Tile::Tile(Vector2i position)
    : _position{ position }, _terrain{ nullptr }, _object{ nullptr }, _mob{ nullptr}
{}

bool Tile::is_solid() const {
    if (_terrain && _terrain->get_solid())
        return true;

    if (_object && _object->get_solid())
        return true;

    if (_mob)
        return true;

    return false;
}

/* Getters & Setters */
Vector2i Tile::get_position() const { return _position; }
Terrain* Tile::get_terrain() { return _terrain; }
Object* Tile::get_object() { return _object; }
Mob* Tile::get_mob() { return _mob; }

void Tile::_set_position(Vector2i position) {
    _position = position;
}

void Tile::_set_terrain(Terrain* terrain) {
    _terrain = terrain;

    if (_terrain)
        _terrain->set_position(_position);
}

void Tile::_set_object(Object* object) {
    _object = object;

    if (_object)
        _object->set_position(_position);
}

void Tile::_set_mob(Mob* mob) {
    _mob = mob;

    if (_mob)
        _mob->set_position(_position);
}
