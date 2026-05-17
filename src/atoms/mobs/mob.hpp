#pragma once

#include "pch.hpp"
#include "atoms/atom.hpp"
#include "behaviors/mob_behavior.hpp"

class Mob : public Atom {
protected:
    std::unique_ptr<MobBehavior> _behavior;

public:
    Mob();

    void ready(Game* ctx) override;
    void tick() override;
    void update(float delta) override;

    // Move the mob to another tile.
    // Returns true on success.
    bool move(Vector2i dest);

};
