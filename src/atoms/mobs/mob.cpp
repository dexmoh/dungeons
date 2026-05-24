#include "atoms/mobs/mob.hpp"

#include "game.hpp"
#include "level.hpp"
#include "tile.hpp"

Mob::Mob(Game& ctx)
    : Atom(ctx, Atom::BaseType::MOB)
{
    _name = "Mob";
}

void Mob::ready() {
    Atom::ready();

    if (_behavior)
        _behavior->ready();
}

void Mob::tick() {
    if (_behavior)
        _behavior->tick();
}

void Mob::update(float delta) {
    // Update movement cooldown if we are moving.
    if (_is_moving) {
        _movement_cooldown -= delta;

        float t = std::max(_movement_cooldown / _movement_duration, 0.0f);
        set_offset({
            std::lerp(0.0f, _initial_offset.x, t),
            std::lerp(0.0f, _initial_offset.y, t)
        });

        if (_movement_cooldown <= 0.0f) {
            _movement_cooldown = 0.0f;
            set_offset({ 0.0f, 0.0f });
            _is_moving = false;
        }
    }

    if (_behavior)
        _behavior->update(delta);

    if (_is_flipping) {
        float rot = get_rotation();
        if (rot > 360.0f) {
            _is_flipping = false;
            set_rotation(0.0f);
        }
        else {
            set_rotation(rot + _flip_speed * delta);
        }
    }
}

bool Mob::try_move(MoveDir dir) {
    if (_is_moving)
        return false;

    Level* level = _ctx.get_level();
    if (!level)
        return false;

    Vector2i move_vec = Vector2i::move_dir_to_vec(dir);
    if (move_vec.is_zero())
        return false;

    bool success = level->move_mob(*this, get_position() + move_vec);
    if (success) {
        _movement_duration = (1.0f / _movement_speed) * move_vec.length();
        _movement_cooldown = _movement_duration;
        _is_moving = true;

        Vector2i tile_size = _ctx.get_tile_size();
        _initial_offset = {
            float(-move_vec.x * tile_size.width()),
            float(-move_vec.y * tile_size.height())
        };
        set_offset(_initial_offset);

        if (move_vec.x < 0)
            set_flip_h(false);
        else if (move_vec.x > 0)
            set_flip_h(true);
    }

    return success;
}

bool Mob::is_moving() const {
    return _is_moving;
}

void Mob::flip() {
    _is_flipping = true;
}

bool Mob::is_flipping() const {
    return _is_flipping;
}

void Mob::set_behavior(std::unique_ptr<MobBehavior> behavior) {
    _behavior = std::move(behavior);
}
