#include "level.hpp"

#include "game.hpp"
#include "tile.hpp"
#include "atoms/terrains/terrain.hpp"
#include "atoms/objects/object.hpp"
#include "atoms/mobs/mob.hpp"
#include "atoms/terrains/floor.hpp"
#include "atoms/terrains/wall.hpp"
#include "atoms/mobs/player.hpp"
#include "util/camera_bounds.hpp"

Level::Level(Vector2i size, std::unique_ptr<Player> player)
    : _size{ size }, _tiles{ nullptr }, _player{ player.get() }, clear_color{ DEFAULT_CLEAR_COLOR }
{
    if (_size.width() < 1 || _size.height() < 1) {
        // TODO: Throw a proper error or something.
        std::cout
            << "ERROR: Couldn't initialize a new level, size of the level was invalid."
            << std::endl;

        return;
    }

    int total_num_of_tiles = _size.width() * _size.height();
    _tiles = new(std::nothrow) Tile[total_num_of_tiles];

    if (!_tiles) {
        // TODO: Here too.
        std::cout
            << "ERROR: Failed to allocate memory while trying to initialize a new level."
            << std::endl;

        return;
    }

    // Initialize tiles.
    for (int x = 0; x < _size.width(); x++) {
        for (int y = 0; y < _size.height(); y++) {
            _tiles[y * _size.width() + x]._set_position({x, y});
        }
    }

    Tile* tile = get_tile(player->get_position());
    if (!tile) {
        // TODO: And here...
        std::cout
            << "ERROR: Failed to spawn a player while initializing the level."
            << std::endl;

        return;
    }

    tile->_set_mob(player.get());
    _atoms.reserve(total_num_of_tiles + 1);
    _atoms.push_back(std::move(player));
}

Level::~Level() {
    if (_tiles) {
        delete[] _tiles;
        _tiles = nullptr;
    }
}

void Level::ready(Game* ctx) {
    for (auto& atom : _atoms)
        atom->ready(ctx);
}

void Level::tick() {
    for (auto& atom : _atoms)
        atom->tick();
}

void Level::update(float delta) {
    for (auto& atom : _atoms)
        atom->update(delta);
}

void Level::draw(CameraBounds bounds) const {
    // Draw terrains.
    for (int y = bounds.start_y; y < bounds.end_y; y++) {
        for (int x = bounds.start_x; x < bounds.end_x; x++) {
            Terrain* terrain = _tiles[y * _size.width() + x].get_terrain();
            if (terrain)
                terrain->draw();
        }
    }

    // Draw objects.
    for (int y = bounds.start_y; y < bounds.end_y; y++) {
        for (int x = bounds.start_x; x < bounds.end_x; x++) {
            Object* object = _tiles[y * _size.width() + x].get_object();
            if (object)
                object->draw();
        }
    }

    // Draw mobs.
    for (int y = bounds.start_y; y < bounds.end_y; y++) {
        for (int x = bounds.start_x; x < bounds.end_x; x++) {
            Mob* mob = _tiles[y * _size.width() + x].get_mob();
            if (mob)
                mob->draw();
        }
    }
}

bool Level::spawn_terrain(std::unique_ptr<Terrain> terrain, Vector2i position, bool force_replace) {
    if (!terrain)
        return false;

    Tile* tile = get_tile(position);
    if (!tile)
        return false;

    Terrain* old_terrain = tile->get_terrain();
    if (old_terrain) {
        if (!force_replace)
            return false;

        int old_terrain_index = _find_atom(old_terrain);

        if (old_terrain_index >= 0)
            _atoms.erase(_atoms.begin() + old_terrain_index);

        tile->_set_terrain(nullptr);
    }

    tile->_set_terrain(terrain.get());
    _atoms.push_back(std::move(terrain));

    return true;
}

bool Level::spawn_object(std::unique_ptr<Object> object, Vector2i position, bool force_replace) {
    return false;
}

bool Level::spawn_mob(std::unique_ptr<Mob> mob, Vector2i position, bool force_replace) {
    return false;
}

bool Level::move_mob(Mob* mob, Vector2i dest) {
    Tile* dest_tile = get_tile(dest);
    if (!dest_tile || dest_tile->is_solid())
        return false;

    Tile* src_tile = get_tile(mob->get_position());
    if (!src_tile)
        return false;

    src_tile->_set_mob(nullptr);
    dest_tile->_set_mob(mob);

    return true;
}

std::unique_ptr<Level> Level::generate_placeholder() {
    auto player = std::make_unique<Player>();
    player->set_position({ 1, 1 });
    
    Vector2i lvl_size = { 50, 30 };
    auto lvl = std::make_unique<Level>(lvl_size, std::move(player));

    for (int x = 0; x < lvl_size.width(); x++) {
        for (int y = 0; y < lvl_size.height(); y++) {
            if (x == 0 || x == lvl_size.width() - 1 || y == 0 || y == lvl_size.height() - 1)
                lvl->spawn_terrain(std::make_unique<Wall>(), { x, y });
            else
                lvl->spawn_terrain(std::make_unique<Floor>(), { x, y });
        }
    }

    return lvl;
}

int Level::_find_atom(Atom* atom) const {
    if (!atom)
        return -1;

    int result = -1;

    for (int i = 0; i < _atoms.size(); i++) {
        if (_atoms[i].get() == atom) {
            result = i;
            break;
        }
    }

    return result;
}

/* Getters & Setters */
Vector2i Level::get_size() const {
    return _size;
}

Tile* Level::get_tile(Vector2i position) const {
    if (position.x < 0 || position.y < 0)
        return nullptr;
    if (position.x >= _size.width() || position.y >= _size.height())
        return nullptr;

    return &_tiles[position.y * _size.width() + position.x];
}
