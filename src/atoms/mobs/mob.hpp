#pragma once

#include "pch.hpp"
#include "atoms/atom.hpp"
#include "behaviors/mob_behavior.hpp"

class Mob : public Atom {
private:
    float _movement_speed;    // Mob's movement speed (in tiles/sec).
    float _movement_cooldown; // Used to prevent the mob from moving again if it is already moving.
    bool _is_moving;          // Set to true if the mob is currently moving.
    float _flip_speed;        // Flip speed (in deg/sec).
    bool _is_flipping;        // Set to true if the mob is currently doing a flip.

    static constexpr float _DEFAULT_MOVEMENT_SPEED = 5.0f; // (tiles/sec)
    static constexpr float _DEFAULT_FLIP_SPEED = 720.0f;   // (deg/sec)

    std::unique_ptr<MobBehavior> _behavior;

public:
    Mob();

    void ready(Game* ctx) override;
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
