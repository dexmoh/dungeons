#include "level.hpp"

#include "game.hpp"
#include "tile.hpp"
#include "atoms/terrains/floor.hpp"
#include "atoms/terrains/wall.hpp"

Level::Level(Vector2i size)
    : _size{ size }, _tiles{ nullptr }, clear_color{ DEFAULT_CLEAR_COLOR }
{
    if (_size.width() > 0 && _size.height() > 0) {
        _tiles = new Tile[_size.width() * _size.height()];

        // Initialize tiles.
        for (int x = 0; x < _size.width(); x++) {
            for (int y = 0; y < _size.height(); y++) {
                _tiles[y * _size.width() + x].set_position({x, y});
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
    for (int i = 0; i < _size.width() * _size.height(); i++)
        _tiles[i].ready(ctx);
}

void Level::tick() {
    for (int i = 0; i < _size.width() * _size.height(); i++)
        _tiles[i].tick();
}

void Level::update(float delta) {
    for (int i = 0; i < _size.width() * _size.height(); i++)
        _tiles[i].update(delta);
}

void Level::draw() const {
    // Draw terrain.
    for (int i = 0; i < _size.width() * _size.height(); i++)
        _tiles[i].draw_terrain();

    // Draw objects.
    for (int i = 0; i < _size.width() * _size.height(); i++)
        _tiles[i].draw_objects();

    // Draw mobs.
    for (int i = 0; i < _size.width() * _size.height(); i++)
        _tiles[i].draw_mob();
}

Vector2i Level::get_size() const { return _size; }

Tile* Level::get_tile(Vector2i position) const {
    if (position.x < 0 || position.y < 0)
        return nullptr;
    if (position.x >= _size.width() || position.y >= _size.height())
        return nullptr;

    return &_tiles[position.y * _size.width() + position.x];
}

std::unique_ptr<Level> Level::generate_placeholder() {
    Vector2i lvl_size = { 18, 12 };
    auto lvl = std::make_unique<Level>(lvl_size);

    for (int x = 0; x < lvl_size.width(); x++) {
        for (int y = 0; y < lvl_size.height(); y++) {
            Tile* tile = lvl->get_tile({x, y});

            if (x == 0 || x == lvl_size.width() - 1 || y == 0 || y == lvl_size.height() - 1)
                tile->set_terrain(std::make_unique<Wall>());
            else
                tile->set_terrain(std::make_unique<Floor>());
        }
    }

    return lvl;
}
