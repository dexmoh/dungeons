#include "tile.hpp"

#include "atoms/terrains/terrain.hpp"
#include "atoms/objects/object.hpp"
#include "atoms/mobs/mob.hpp"
#include "atoms/areas/area.hpp"

Tile::Tile()
    : _position{ 0, 0 }
{}

Tile::Tile(Vector2i position)
    : _position{ position }
{}

Tile::~Tile()
{}

void Tile::draw(float delta) {
    if (_terrain)
        _terrain->draw(delta);
    
    for (auto& obj : _objects)
        if (obj)
            obj->draw(delta);

    if (_mob)
        _mob->draw(delta);

    if (_area)
        _area->draw(delta);
}

Vector2i Tile::get_position() const { return _position; }
void Tile::set_position(Vector2i position) { _position = position; }
