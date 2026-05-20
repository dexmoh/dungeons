#pragma once

#include "pch.hpp"

class Game;
class Mob;

class MobBehavior {
protected:
    Mob& _mob;
    Game& _ctx;

public:
    MobBehavior(Mob& mob, Game& ctx);

    virtual void ready();
    virtual void tick();
    virtual void update(float delta);

};
