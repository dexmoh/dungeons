#pragma once

#include "pch.hpp"

class Game;

// Class for managing camera data and logic.
class CameraController {
private:
    Game* _ctx;         // Game context.
    Camera2D _camera;   // Raylib camera container.
    Vector2i _position; // Camera's position in the world grid.

public:
    static constexpr float MIN_ZOOM     = 0.5f;
    static constexpr float MAX_ZOOM     = 20.0f;
    static constexpr float DEFAULT_ZOOM = 2.0f;
    static constexpr float ZOOM_FACTOR  = 1.8f;

public:
    CameraController();

    // Initialize camera.
    void init(Game* ctx);

    // Called every frame.
    void update(float delta);

    // Recenter camera offset to be in the middle of the screen.
    void recenter();

    
    Camera2D get_rl_camera() const; // Returns raylib Camera2D container.
    float get_rotation() const;     // Get current camera rotation.

    void set_position(Vector2i position);  // Change camera's position.
    void set_rotation(float new_rotation); // Set new camera rotation.

};
