#include "game.hpp"

#include "level.hpp"
#include "camera_controller.hpp"
#include "atoms/mobs/player.hpp"

Game::Game()
    : _tile_size{ _DEFAULT_TILE_SIZE, _DEFAULT_TILE_SIZE },
      _tps{ DEFAULT_TPS },
      _camera{ *this }
{
    // Create a maximized raylib window.
    InitWindow(800, 600, "Dungeons");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    MaximizeWindow();
    SetTargetFPS(_DEFAULT_TARGET_FPS);

    // Load and initialize textures.
    _tex_manager.init();

    // Initialize camera.
    _camera.init();
}

Game::~Game() {
    CloseWindow();
}

void Game::run() {
    // Load a level.
    if (!_level)
        _level = Level::generate_placeholder(*this);
    _level->ready();
    _camera.set_target(_level->get_player());

    float tick_counter = 0.0f;

    // Game loop.
    while (!WindowShouldClose()) {
        const float delta = GetFrameTime();

        if (IsWindowResized())
            window_resized.emit(GetScreenWidth(), GetScreenHeight());

        // Handle game ticks.
        tick_counter += delta;
        if (tick_counter > (1.0f / _tps)) {
            tick_counter = 0.0f;
            _level->tick();
        }

        // Update calls.
        _level->update(delta);
        _camera.update(delta);

        // Draw to the screen.
        BeginDrawing();
            ClearBackground(_level->clear_color);

            // Draw game world.
            BeginMode2D(_camera.get_rl_camera());
                // Temporary debug lines.
                DrawLine(-2000, 0, 2000, 0, RED);
                DrawLine(0, -2000, 0, 2000, GREEN);

                _level->draw(_camera.get_bounds());
            EndMode2D();

            DrawText(std::format("Delta: {}", delta).c_str(), 30, 30, 20, RED);
            DrawFPS(30, 55);
        EndDrawing();
    }
}

/* Getters & Setters */
Level* Game::get_level() { return _level.get(); }
TextureManager& Game::get_tex_manager() { return _tex_manager; }
RandomNumberGenerator& Game::get_rng() { return _rng; }
CameraController& Game::get_camera() { return _camera; }
Vector2i Game::get_tile_size() const { return _tile_size; }
float Game::get_tps() const { return _tps; }

void Game::set_tps(float new_tps) { _tps = new_tps; }
