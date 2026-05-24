#pragma once

#include "pch.hpp"
#include "atoms/atom.hpp"
#include "behaviors/mob_behavior.hpp"

class Mob : public Atom {
private:
    static constexpr float _DEFAULT_MOVEMENT_SPEED = 5.0f; // (tiles/sec)
    static constexpr float _DEFAULT_FLIP_SPEED = 720.0f;   // (deg/sec)

    float _movement_speed = _DEFAULT_MOVEMENT_SPEED;
    float _movement_cooldown = 0.0f;
    float _movement_duration = 0.0f;
    float _flip_speed = _DEFAULT_FLIP_SPEED;
    Vector2 _initial_offset = { 0.0f, 0.0f };
    bool _is_moving = false;
    bool _is_flipping = false;

    std::unique_ptr<MobBehavior> _behavior;

protected:
    Mob(Game& ctx);

public:
    void ready() override;
    void tick() override;
    void update(float delta) override;

    // Try to move the mob to a nearby tile. Returns true on success.
    // Fails to move if movement is on cooldown.
    bool try_move(MoveDir dir);
    bool is_moving() const;

    // Do a flip!
    void flip();
    bool is_flipping() const;

    void set_behavior(std::unique_ptr<MobBehavior> behavior);

};
