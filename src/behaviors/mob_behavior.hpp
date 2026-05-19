#pragma once

#include "pch.hpp"

class Game;
class Mob;

class MobBehavior {
protected:
    Mob* _mob;
    Game* _ctx;

public:
    MobBehavior(Mob& mob);

    virtual void ready(Game& ctx);
    virtual void tick();
    virtual void update(float delta);

};
