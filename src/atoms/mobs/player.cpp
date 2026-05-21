#include "atoms/mobs/player.hpp"

#include "behaviors/player_behavior.hpp"

Player::Player(Game& ctx)
    : Mob(ctx)
{
    _name = "Player";
    _description = "It's you!";
    set_behavior(std::make_unique<PlayerBehavior>(*this, ctx));
}
