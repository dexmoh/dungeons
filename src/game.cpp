#include "game.hpp"

#include "level.hpp"

Game::Game()
    : _tps{ 10.0f }
{
    // Create a maximized raylib window.
    InitWindow(640, 480, "Dungeons");
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    MaximizeWindow();
    SetTargetFPS(60);
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

        BeginDrawing();
            ClearBackground(SKYBLUE);

            if (_level)
                _level->draw(delta);

            DrawText(std::format("Delta: {}", delta).c_str(), 30, 30, 20, RED);
            DrawFPS(30, 55);
        EndDrawing();
    }
}
