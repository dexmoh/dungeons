#include "tile.hpp"

#include "game.hpp"
#include "atoms/objects/object.hpp"
#include "atoms/mobs/mob.hpp"

Tile::Tile()
    : _position{ Vector2i::ZERO }
{}

Tile::Tile(Vector2i position)
    : _position{ position }
{
    _terrain.set_position(_position);
}

Tile::~Tile()
{}

void Tile::ready(Game* ctx) {
    _terrain.ready(ctx);
    
    for (Object& obj : _objects)
        obj.ready(ctx);

    if (_mob)
        _mob->ready(ctx);
}

void Tile::tick() {
    _terrain.tick();

    for (Object& obj : _objects)
        obj.tick();

    if (_mob)
        _mob->tick();
}

void Tile::draw_terrain() const {
    _terrain.draw();
}

void Tile::draw_objects() const {
    for (const Object& obj : _objects)
        obj.draw();
}

void Tile::draw_mob() const {
    if (_mob)
        _mob->draw();
}

/* Getters & Setters */
Vector2i Tile::get_position() const { return _position; }
Terrain& Tile::get_terrain() { return _terrain; }
std::vector<Object> Tile::get_objects() { return _objects; }

void Tile::set_position(Vector2i position) {
    _position = position;
    _terrain.set_position(_position);
}

void Tile::set_terrain(Terrain terrain) { _terrain = terrain; }
