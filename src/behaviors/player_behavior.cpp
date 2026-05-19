#include "behaviors/player_behavior.hpp"

#include "game.hpp"
#include "atoms/mobs/player.hpp"
#include "camera_controller.hpp"

PlayerBehavior::PlayerBehavior(Mob& mob)
    : MobBehavior(mob),
      _camera{ nullptr }
{}

void PlayerBehavior::ready(Game& ctx) {
    MobBehavior::ready(ctx);
    _camera = &(ctx.get_camera());
}

void PlayerBehavior::update(float delta) {
    if (IsKeyPressed(KEY_R))
        _mob->flip();

    if (_mob->is_moving())
        return;

    // Handle movement.
    bool up = IsKeyDown(KEY_UP) || IsKeyDown(KEY_KP_8);
    bool down = IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_KP_2);
    bool left = IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_KP_4);
    bool right = IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_KP_6);
    bool up_left = IsKeyDown(KEY_KP_7) || (up && left);
    bool up_right = IsKeyDown(KEY_KP_9) || (up && right);
    bool down_left = IsKeyDown(KEY_KP_1) || (down && left);
    bool down_right = IsKeyDown(KEY_KP_3) || (down && right);

    if (up_left)
        _mob->try_move(MoveDir::UP_LEFT);
    else if (up_right)
        _mob->try_move(MoveDir::UP_RIGHT);
    else if (down_left)
        _mob->try_move(MoveDir::DOWN_LEFT);
    else if (down_right)
        _mob->try_move(MoveDir::DOWN_RIGHT);
    else if (up)
        _mob->try_move(MoveDir::UP);
    else if (down)
        _mob->try_move(MoveDir::DOWN);
    else if (left)
        _mob->try_move(MoveDir::LEFT);
    else if (right)
        _mob->try_move(MoveDir::RIGHT);
}
