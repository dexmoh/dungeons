#include "tile.hpp"

#include "atoms/atom.hpp"
#include "atoms/terrains/terrain.hpp"
#include "atoms/objects/object.hpp"
#include "atoms/mobs/mob.hpp"

Tile::Tile(Vector2i position)
    : _position{ position }
{}

bool Tile::_try_add(Atom* atom) {
    if (!atom)
        return false;

    if (contains(atom))
        return false;

    switch (atom->BASE_TYPE) {
        case Atom::BaseType::TERRAIN: {
            if (_terrain)
                return false;

            _terrain = static_cast<Terrain*>(atom);
            _terrain->set_position(_position);
            return true;
        }
        case Atom::BaseType::OBJECT: {
            Object* obj = static_cast<Object*>(atom);
            obj->set_position(_position);
            _objects.push_back(obj);
            return true;
        }
        case Atom::BaseType::MOB: {
            Mob* mob = static_cast<Mob*>(atom);
            mob->set_position(_position);
            _mobs.push_back(mob);
            return true;
        }
        default:
            return false;
    }
}

bool Tile::_try_remove(Atom* atom) {
    if (!atom)
        return false;

    switch (atom->BASE_TYPE) {
        case Atom::BaseType::TERRAIN: {
            if (_terrain == static_cast<Terrain*>(atom)) {
                _terrain = nullptr;
                return true;
            }
            else
                return false;
        }
        case Atom::BaseType::OBJECT: {
            auto obj_it = std::find(
                _objects.begin(), _objects.end(), static_cast<Object*>(atom)
            );

            if (obj_it != _objects.end()) {
                _objects.erase(obj_it);
                return true;
            }
            else
                return false;
        }
        case Atom::BaseType::MOB: {
            auto mob_it = std::find(
                _mobs.begin(), _mobs.end(), static_cast<Mob*>(atom)
            );

            if (mob_it != _mobs.end()) {
                _mobs.erase(mob_it);
                return true;
            }
            else
                return false;
        }
        default:
            return false;
    }
}

bool Tile::is_solid() const {
    if (_terrain && _terrain->get_solid())
        return true;

    for (const auto* obj : _objects)
        if (obj && obj->get_solid())
            return true;

    for (const auto* mob : _mobs)
        if (mob && mob->get_solid())
            return true;

    return false;
}

bool Tile::contains(Atom* atom) const {
    if (!atom)
        return false;

    switch (atom->BASE_TYPE) {
        case Atom::BaseType::TERRAIN: {
            if (_terrain == static_cast<Terrain*>(atom))
                return true;
            else
                return false;
        }
        case Atom::BaseType::OBJECT: {
            auto obj_it = std::find(
                _objects.begin(), _objects.end(), static_cast<Object*>(atom)
            );

            if (obj_it != _objects.end())
                return true;
            else
                return false;
        }
        case Atom::BaseType::MOB: {
            auto mob_it = std::find(
                _mobs.begin(), _mobs.end(), static_cast<Mob*>(atom)
            );

            if (mob_it != _mobs.end())
                return true;
            else
                return false;
        }
        default:
            return false;
    }
}

/* Getters */
Vector2i Tile::get_position() const { return _position; }
Terrain* Tile::get_terrain() { return _terrain; }
const std::vector<Object*>& Tile::get_objects() const { return _objects; }
const std::vector<Mob*>& Tile::get_mobs() const { return _mobs; }
