#include "tile.hpp"

#include "game.hpp"
#include "atoms/terrains/terrain.hpp"
#include "atoms/objects/object.hpp"
#include "atoms/mobs/mob.hpp"

Tile::Tile()
    : _position{ 0, 0 }
{}

Tile::Tile(Vector2i position)
    : _position{ position }
{}

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

void Tile::draw(float delta) {
    if (_terrain)
        _terrain->draw(delta);
    
    for (auto& obj : _objects)
        if (obj)
            obj->draw(delta);

    if (_mob)
        _mob->draw(delta);
}

Vector2i Tile::get_position() const { return _position; }

void Tile::set_position(Vector2i position) { _position = position; }
void Tile::set_terrain(std::unique_ptr<Terrain> terrain) { _terrain = std::move(terrain); }
