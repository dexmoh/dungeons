#pragma once

#include "pch.hpp"
#include "behaviors/mob_behavior.hpp"

class PlayerBehavior : public MobBehavior {
public:
    PlayerBehavior(Mob* mob);
    
    void update(float delta) override;

};
