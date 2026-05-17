#pragma once

#include "pch.hpp"
#include "camera_controller.hpp"
#include "texture_manager.hpp"

class Level;

// Class for managing game context and the main game loop.
class Game {
private:
    std::unique_ptr<Level> _level; // Currently loaded level.
    TextureManager _tex_manager;   // Texture storage.
    CameraController _camera;      // Main camera.
    Vector2i _tile_size;           // Size of tiles in pixels.
    float _tps;                    // Tick rate.

    static constexpr int _DEFAULT_TARGET_FPS = 60;
    static constexpr int _DEFAULT_TILE_SIZE  = 32;

public:
    static constexpr float DEFAULT_TPS = 10.0f;

public:
    Game();
    ~Game();

    void run();

    Level* get_level();
    const TextureManager& get_tex_manager() const;
    Vector2i get_tile_size() const;
    float get_tps() const;

    void set_tps(float new_tps);

};
