#include "level.hpp"

#include "game.hpp"
#include "tile.hpp"
#include "atoms/atom.hpp"
#include "atoms/terrains/terrain.hpp"
#include "atoms/terrains/floor.hpp"
#include "atoms/terrains/wall.hpp"
#include "atoms/objects/object.hpp"
#include "atoms/mobs/mob.hpp"
#include "atoms/mobs/player.hpp"
#include "util/camera_bounds.hpp"

Level::Level(Vector2i size, std::unique_ptr<Player> player)
    : _size{ size }, _player{ player.get() }
{
    if (_size.width() < 1 || _size.height() < 1) {
        Log::write(
            "Couldn't initialize a new level because the provided size was invalid.",
            Log::Level::ERROR
        );

        // TODO: Throw exception.
    }

    int total_num_of_tiles = _size.width() * _size.height();
    _tiles = new(std::nothrow) Tile[total_num_of_tiles];
    _terrains.reserve(total_num_of_tiles);

    if (!_tiles) {
        Log::write(
            "Failed to allocate enough memory while trying to initialize a new level.",
            Log::Level::ERROR
        );
        
        // TODO: Throw exception.
    }

    // Initialize tiles.
    for (int x = 0; x < _size.width(); x++) {
        for (int y = 0; y < _size.height(); y++) {
            _tiles[y * _size.width() + x] = Tile({x, y});
        }
    }

    if (!player) {
        Log::write(
            "Couldn't initialize a new level, provided player is null.",
            Log::Level::ERROR
        );

        // TODO: Throw exception.
    }

    Tile* tile = get_tile(player->get_position());
    if (!tile) {
        Log::write(
            std::format(
                "Failed to spawn the player at position [{}, {}] while initializing a new level.",
                player->get_position().x, player->get_position().y
            ),
            Log::Level::ERROR
        );

        // TODO: Throw exception.
    }

    _player->deleted.connect(
        [this]() {
            Log::write(
                "Player got deleted from the level. This probably shouldn't have happened!",
                Log::Level::ERROR
            );
            _player = nullptr;
        }
    );

    tile->_try_add(player.get());
    _mobs.push_back(std::move(player));
}

Level::~Level() {
    if (_tiles) {
        delete[] _tiles;
        _tiles = nullptr;
    }
}

void Level::ready() {
    _process_spawn_queue();
}

void Level::tick() {
    for (auto& terrain : _terrains)
        terrain->tick();

    for (auto& obj : _objects)
        obj->tick();

    for (auto& mob : _mobs)
        mob->tick();
}

void Level::update(float delta) {
    for (auto& terrain : _terrains)
        terrain->update(delta);

    for (auto& obj : _objects)
        obj->update(delta);

    for (auto& mob : _mobs)
        mob->update(delta);

    _process_deletion_queue();
    _process_spawn_queue();
}

void Level::draw(CameraBounds bounds) const {
    // Draw terrains.
    for (int y = bounds.start_y; y < bounds.end_y; y++) {
        for (int x = bounds.start_x; x < bounds.end_x; x++) {
            const Terrain* terrain = _tiles[y * _size.width() + x].get_terrain();
            if (terrain)
                terrain->draw();
        }
    }

    // Draw objects.
    for (const auto& obj : _objects) {
        if (!obj)
            continue;

        Vector2i pos = obj->get_position();
        if (pos.x >= bounds.start_x && pos.x <= bounds.end_x)
            if (pos.y >= bounds.start_y && pos.y <= bounds.end_y)
                obj->draw();
    }

    // Draw mobs.
    for (const auto& mob : _mobs) {
        if (!mob)
            continue;

        Vector2i pos = mob->get_position();
        if (pos.x >= bounds.start_x && pos.x <= bounds.end_x)
            if (pos.y >= bounds.start_y && pos.y <= bounds.end_y)
                mob->draw();
    }
}

bool Level::move_mob(Mob& mob, Vector2i dest) {
    Tile* dest_tile = get_tile(dest);
    if (!dest_tile || dest_tile->is_solid())
        return false;

    Tile* src_tile = get_tile(mob.get_position());
    if (!src_tile)
        return false;

    src_tile->_try_remove(&mob);
    dest_tile->_try_add(&mob);

    return true;
}

void Level::queue_spawn(std::unique_ptr<Atom> atom) {
    if (atom)
        _spawn_queue.push_back(
            std::move(atom)
        );
}

void Level::queue_delete(Atom* atom) {
    if (atom)
        _deletion_queue.push_back(atom);
}

void Level::_process_spawn_queue() {
    for (auto& atom : _spawn_queue) {
        if (!atom)
            continue;

        Tile* tile = get_tile(atom->get_position());
        if (!tile)
            continue;

        bool success = tile->_try_add(atom.get());
        if (!success)
            continue;

        switch (atom->BASE_TYPE) {
            case Atom::BaseType::TERRAIN: {
                auto terrain = std::unique_ptr<Terrain>(
                    static_cast<Terrain*>(atom.release())
                );

                auto terrain_it = std::upper_bound(
                    _terrains.begin(), _terrains.end(), terrain,
                    [](const std::unique_ptr<Terrain>& val, const std::unique_ptr<Terrain>& element) {
                        return val->get_z_index() < element->get_z_index();
                    }
                );

                terrain->ready();
                _terrains.insert(terrain_it, std::move(terrain));
                break;
            }
            case Atom::BaseType::OBJECT: {
                auto obj = std::unique_ptr<Object>(
                    static_cast<Object*>(atom.release())
                );

                auto obj_it = std::upper_bound(
                    _objects.begin(), _objects.end(), obj,
                    [](const std::unique_ptr<Object>& val, const std::unique_ptr<Object>& element) {
                        return val->get_z_index() < element->get_z_index();
                    }
                );

                obj->ready();
                _objects.insert(obj_it, std::move(obj));
                break;
            }
            case Atom::BaseType::MOB: {
                auto mob = std::unique_ptr<Mob>(
                    static_cast<Mob*>(atom.release())
                );

                auto mob_it = std::upper_bound(
                    _mobs.begin(), _mobs.end(), mob,
                    [](const std::unique_ptr<Mob>& val, const std::unique_ptr<Mob>& element) {
                        return val->get_z_index() < element->get_z_index();
                    }
                );

                mob->ready();
                _mobs.insert(mob_it, std::move(mob));
                break;
            }
            default:
                tile->_try_remove(atom.get());
                break;
        }
    }
    
    _spawn_queue.clear();
}

void Level::_process_deletion_queue() {
    for (Atom* atom : _deletion_queue) {
        if (!atom)
            continue;

        atom->deleted.emit();

        // Remove atom from its tile.
        Tile* tile = get_tile(atom->get_position());
        if (tile) {
            bool success = tile->_try_remove(atom);
            if (!success)
                Log::write(
                    "Failed to remove an atom from a tile while processing level deletion queue.",
                    Log::Level::ERROR
                );
        }
        else
            Log::write(
                "Couldn't find a tile to which the atom belongs to while trying to delete it.",
                Log::Level::ERROR
            );

        // Find which vector owns this atom and erase it from it.
        switch (atom->BASE_TYPE) {
            case Atom::BaseType::TERRAIN: {
                Terrain* terrain = static_cast<Terrain*>(atom);
                auto terrain_it = std::find_if(
                    _terrains.begin(), _terrains.end(),
                    [terrain](const std::unique_ptr<Terrain>& t) {
                        return t.get() == terrain;
                    }
                );

                if (terrain_it != _terrains.end())
                    _terrains.erase(terrain_it);

                break;
            }
            case Atom::BaseType::OBJECT: {
                Object* obj = static_cast<Object*>(atom);
                auto obj_it = std::find_if(
                    _objects.begin(), _objects.end(),
                    [obj](const std::unique_ptr<Object>& o) {
                        return o.get() == obj;
                    }
                );

                if (obj_it != _objects.end())
                    _objects.erase(obj_it);

                break;
            }
            case Atom::BaseType::MOB: {
                Mob* mob = static_cast<Mob*>(atom);
                auto mob_it = std::find_if(
                    _mobs.begin(), _mobs.end(),
                    [mob](const std::unique_ptr<Mob>& m) {
                        return m.get() == mob;
                    }
                );

                if (mob_it != _mobs.end())
                    _mobs.erase(mob_it);

                break;
            }
            default: {
                Log::write(
                    "Couldn't delete an atom while processing level deletion queue."
                    "This is probably a memory leak. :)",
                    Log::Level::ERROR
                );

                break;
            }
        }
    }

    _deletion_queue.clear();
}

std::unique_ptr<Level> Level::generate_placeholder(Game& ctx) {
    auto player = std::make_unique<Player>(ctx);
    player->set_position({ 1, 1 });
    
    Vector2i lvl_size = { 50, 30 };
    auto lvl = std::make_unique<Level>(lvl_size, std::move(player));

    for (int x = 0; x < lvl_size.width(); x++) {
        for (int y = 0; y < lvl_size.height(); y++) {
            if (x == 0 || x == lvl_size.width() - 1 || y == 0 || y == lvl_size.height() - 1) {
                auto wall = std::make_unique<Wall>(ctx);
                wall->set_position({x, y});
                lvl->queue_spawn(std::move(wall));
            }
            else {
                auto floor = std::make_unique<Floor>(ctx);
                floor->set_position({x, y});
                lvl->queue_spawn(std::move(floor));
            }
        }
    }

    return lvl;
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

Player* Level::get_player() {
    return _player;
}
