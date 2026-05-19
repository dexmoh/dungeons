#pragma once

#include "pch.hpp"
#include "util/camera_bounds.hpp"

class Game;
class Atom;

// Class for managing camera data and logic.
class CameraController {
private:
    Game* _ctx;           // Game context.
    Atom* _target;        // Atom that the camera follows.
    Camera2D _camera;     // Raylib camera container.
    Vector2i _position;   // Camera's position in the world grid.
    Vector2 _offset;      // Offset from the original position.
    CameraBounds _bounds; // Camera's world bounding box.

private:
    void _recenter();           // Recenter camera offset to be in the middle of the screen.
    void _recalculate_bounds(); // Recalculate camera's bounding box in world coordinates.

public:
    static constexpr float MIN_ZOOM     = 0.5f;
    static constexpr float MAX_ZOOM     = 20.0f;
    static constexpr float DEFAULT_ZOOM = 2.0f;
    static constexpr float ZOOM_FACTOR  = 1.8f;

public:
    CameraController();

    // Initialize camera.
    void init(Game& ctx);

    // Called every frame.
    void update(float delta);

    Atom* get_target();              // Get current target.
    Camera2D get_rl_camera() const;  // Returns raylib Camera2D container.
    CameraBounds get_bounds() const; // Get camera bounds clamped to level size.

    void set_target(Atom* target);
    void set_position(Vector2i position, bool recalculate_bounds = true);
    void set_offset(Vector2 offset, bool recalculate_bounds = true);

};
