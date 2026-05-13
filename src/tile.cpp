#include "tile.hpp"

#include "game.hpp"
#include "atoms/terrains/terrain.hpp"
#include "atoms/objects/object.hpp"
#include "atoms/mobs/mob.hpp"

Tile::Tile()
    : _position{ Vector2i::ZERO }
{}

Tile::Tile(Vector2i position)
    : _position{ position }
{
    if (_terrain)
        _terrain->set_position(_position);
}

Tile::~Tile()
{}

void Tile::ready(Game* ctx) {
    if (_terrain)
        _terrain->ready(ctx);
    
    for (auto& obj : _objects)
        if (obj)
            obj->ready(ctx);

    if (_mob)
        _mob->ready(ctx);
}

void Tile::tick() {
    if (_terrain)
        _terrain->tick();

    for (auto& obj : _objects)
        if (obj)
            obj->tick();

    if (_mob)
        _mob->tick();
}

void Tile::update(float delta) {
    if (_terrain)
        _terrain->update(delta);
    
    for (auto& obj : _objects)
        if (obj)
            obj->update(delta);

    if (_mob)
        _mob->update(delta);
}

void Tile::draw_terrain() const {
    if (_terrain)
        _terrain->draw();
}

void Tile::draw_objects() const {
    for (const auto& obj : _objects)
        if (obj)
            obj->draw();
}

void Tile::draw_mob() const {
    if (_mob)
        _mob->draw();
}

/* Getters & Setters */
Vector2i Tile::get_position() const { return _position; }
Terrain* Tile::get_terrain() { return _terrain.get(); }

void Tile::set_position(Vector2i position) {
    _position = position;

    if (_terrain)
        _terrain->set_position(_position);
}

void Tile::set_terrain(std::unique_ptr<Terrain> terrain) {
    _terrain = std::move(terrain);

    if (_terrain)
        _terrain->set_position(_position);
}
