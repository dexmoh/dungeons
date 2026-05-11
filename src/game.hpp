#pragma once

#include "pch.hpp"
#include "camera_controller.hpp"

class Level;

// Class for managing game context and the main game loop.
class Game {
private:
    std::unique_ptr<Level> _level; // Currently loaded level.
    CameraController _camera;      // Main camera.
    Vector2i _tile_size;           // Size of tiles in pixels.
    float _tps;                    // Tick rate.

    static constexpr int _S_DEFAULT_TARGET_FPS = 60;
    static constexpr float _S_DEFAULT_TPS = 10.0f;

public:
    Game();
    ~Game();

    void run();

    Vector2i get_tile_size() const;

};
