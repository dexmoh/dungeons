#include "atoms/mobs/player.hpp"

#include "behaviors/player_behavior.hpp"

Player::Player() {
    _behavior = std::make_unique<PlayerBehavior>(this);
}
