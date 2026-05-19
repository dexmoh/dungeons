#pragma once

#include "pch.hpp"
#include "behaviors/mob_behavior.hpp"

class CameraController;

class PlayerBehavior : public MobBehavior {
private:
    CameraController* _camera;

public:
    PlayerBehavior(Mob& mob);
    
    void ready(Game& ctx) override;
    void update(float delta) override;

};
