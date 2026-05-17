#include "behaviors/mob_behavior.hpp"

#include "game.hpp"
#include "atoms/mobs/mob.hpp"

MobBehavior::MobBehavior(Mob* mob)
    : _mob{ mob },
      _ctx{ nullptr }
{}

void MobBehavior::ready(Game* ctx) { _ctx = ctx; }
void MobBehavior::tick() {}
void MobBehavior::update(float delta) {}
