#include "behaviors/mob_behavior.hpp"

#include "game.hpp"
#include "atoms/mobs/mob.hpp"

MobBehavior::MobBehavior(Mob& mob, Game& ctx)
    : _mob{ mob },
      _ctx{ ctx }
{}

void MobBehavior::ready() {}
void MobBehavior::tick() {}
void MobBehavior::update(float delta) {}
