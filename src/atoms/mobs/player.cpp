#include "atoms/mobs/player.hpp"

#include "behaviors/player_behavior.hpp"

Player::Player() {
    set_behavior(std::make_unique<PlayerBehavior>(*this));
}
