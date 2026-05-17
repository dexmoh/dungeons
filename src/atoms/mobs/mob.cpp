#include "atoms/mobs/mob.hpp"

#include "game.hpp"
#include "level.hpp"
#include "tile.hpp"

Mob::Mob() {}

void Mob::ready(Game* ctx) {
    Atom::ready(ctx);

    if (_behavior)
        _behavior->ready(ctx);
}

void Mob::tick() {
    if (_behavior)
        _behavior->tick();
}

void Mob::update(float delta) {
    if (_behavior)
        _behavior->update(delta);
}

bool Mob::move(Vector2i dest) {
    Level* level = _ctx->get_level();
    if (!level)
        return false;

    return level->move_mob(this, dest);
}
