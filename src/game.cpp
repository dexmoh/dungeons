#include "game.hpp"

#include "level.hpp"
#include "camera_controller.hpp"

Game::Game()
    : _tile_size{ _DEFAULT_TILE_SIZE, _DEFAULT_TILE_SIZE },
      _tps{ DEFAULT_TPS }
{
    // Create a maximized raylib window.
    InitWindow(800, 600, "Dungeons");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    MaximizeWindow();
    SetTargetFPS(_DEFAULT_TARGET_FPS);

    // Load and initialize textures.
    _tex_manager.init();

    // Initialize camera.
    _camera.init(this);
}

Game::~Game() {
    CloseWindow();
}

void Game::run() {
    // Load a level.
    if (!_level)
        _level = Level::generate_placeholder();
        _level->ready(this);

    float tick_counter = 0.0f;

    // Game loop.
    while (!WindowShouldClose()) {
        const float delta = GetFrameTime();

        // Handle game ticks.
        tick_counter += delta;
        if (tick_counter > (1.0f / _tps)) {
            tick_counter = 0.0f;
            _level->tick();
        }

        // Update calls.
        _camera.update(delta);
        _level->update(delta);

        // Draw to the screen.
        BeginDrawing();
            ClearBackground(_level->clear_color);

            // Draw game world.
            BeginMode2D(_camera.get_rl_camera());
                // Temporary debug lines.
                DrawLine(-2000, 0, 2000, 0, RED);
                DrawLine(0, -2000, 0, 2000, GREEN);

                _level->draw();
            EndMode2D();

            DrawText(std::format("Delta: {}", delta).c_str(), 30, 30, 20, RED);
            DrawFPS(30, 55);
        EndDrawing();
    }
}

/* Getters & Setters */
Level* Game::get_level() { return _level.get(); }
const TextureManager& Game::get_tex_manager() const { return _tex_manager; }
Vector2i Game::get_tile_size() const { return _tile_size; }
float Game::get_tps() const { return _tps; }

void Game::set_tps(float new_tps) { _tps = new_tps; }
