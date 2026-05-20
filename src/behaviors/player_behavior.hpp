#pragma once

#include "pch.hpp"
#include "behaviors/mob_behavior.hpp"

class CameraController;

class PlayerBehavior : public MobBehavior {
private:
    CameraController& _camera;

public:
    PlayerBehavior(Mob& mob, Game& ctx);

    void update(float delta) override;

};
