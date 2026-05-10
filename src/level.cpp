#include "level.hpp"

#include "game.hpp"
#include "tile.hpp"
#include "atoms/terrains/terrain.hpp"

Level::Level(Vector2i size)
    : _size{ size }, _tiles{ nullptr }
{
    if (_size.x > 0 && _size.y > 0) {
        _tiles = new Tile[size.x * size.y];

        // Initialize tiles.
        for (int x = 0; x < _size.x; x++) {
            for (int y = 0; y < _size.y; y++) {
                _tiles[y * _size.x + x].set_position({x, y});
            }
        }
    }
    else {
        // TODO: Throw a proper error or something.
        std::cout
            << "ERROR: Couldn't initialize a new level, size of the level was invalid."
            << std::endl;
    }
}

Level::~Level() {
    if (_tiles) {
        delete[] _tiles;
        _tiles = nullptr;
    }
}

void Level::ready(Game* ctx) {
    for (int y = 0; y < _size.y; y++) {
        for (int x = 0; x < _size.x; x++) {
            _tiles[y * _size.x + x].ready(ctx);
        }
    }
}

void Level::tick() {
    for (int y = 0; y < _size.y; y++) {
        for (int x = 0; x < _size.x; x++) {
            _tiles[y * _size.x + x].tick();
        }
    }
}

void Level::draw(float delta) {
    for (int y = 0; y < _size.y; y++) {
        for (int x = 0; x < _size.x; x++) {
            _tiles[y * _size.x + x].draw(delta);
        }
    }
}

Tile* Level::get_tile(Vector2i position) const {
    if (position.x < 0 || position.y < 0)
        return nullptr;
    if (position.x >= _size.x || position.y >= _size.y)
        return nullptr;

    return &_tiles[position.y * _size.x + position.x];
}

std::unique_ptr<Level> Level::generate_placeholder() {
    Vector2i lvl_size = { 100, 100 };
    auto lvl = std::make_unique<Level>(lvl_size);

    for (int x = 0; x < lvl_size.x; x++) {
        for (int y = 0; y < lvl_size.y; y++) {
            auto terrain = std::make_unique<Terrain>();
            terrain->set_position({x, y});

            Tile* tile = lvl->get_tile({x, y});
            tile->set_terrain(std::move(terrain));
        }
    }

    return lvl;
}
