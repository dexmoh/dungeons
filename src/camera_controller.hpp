#pragma once

#include "pch.hpp"

class Game;

// Class for managing camera data and logic.
class CameraController {
private:
    Game* _ctx;         // Game context.
    Camera2D _camera;   // Raylib camera container.
    Vector2i _position; // Camera's position in the world grid.

    static constexpr float _S_MIN_ZOOM = 0.5f;
    static constexpr float _S_MAX_ZOOM = 20.0f;
    static constexpr float _S_DEFAULT_ZOOM = 2.0f;
    static constexpr float _S_ZOOM_FACTOR = 1.5f;

public:
    CameraController();

    // Initialize camera.
    void init(Game* ctx);

    // Called every frame.
    void update(float delta);

    // Recenter camera offset to be in the middle of the screen.
    void recenter();

    // Returns raylib Camera2D container.
    Camera2D get_rl_camera() const;

    // Change camera's position.
    void set_position(Vector2i position);

};
