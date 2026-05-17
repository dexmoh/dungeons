#include "behaviors/player_behavior.hpp"

#include "atoms/mobs/mob.hpp"

PlayerBehavior::PlayerBehavior(Mob* mob)
    : MobBehavior(mob), is_rotating{ false }
{}

void PlayerBehavior::update(float delta) {
    // Handle movement.
    if (IsKeyPressed(KEY_W)) {
        _mob->move(_mob->get_position() + Vector2i::UP);
    }
    else if (IsKeyPressed(KEY_S)) {
        _mob->move(_mob->get_position() + Vector2i::DOWN);
    }
    else if (IsKeyPressed(KEY_A)) {
        _mob->move(_mob->get_position() + Vector2i::LEFT);
    }
    else if (IsKeyPressed(KEY_D)) {
        _mob->move(_mob->get_position() + Vector2i::RIGHT);
    }
    else if (IsKeyPressed(KEY_R)) {
        is_rotating = true;
    }

    if (is_rotating) {
        float rotation = _mob->get_rotation();
        if (rotation > 360.0f) {
            is_rotating = false;
            _mob->set_rotation(0.0f);
        }
        else {
            _mob->set_rotation(rotation + 600.0f * delta);
        }
    }
}
