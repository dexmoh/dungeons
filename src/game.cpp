#include "game.hpp"

#include "level.hpp"

Game::Game() {
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
    if (!_level)
        _level = Level::generate_placeholder();

    while (!WindowShouldClose()) {
        const float delta = GetFrameTime();

        BeginDrawing();
            ClearBackground(SKYBLUE);

            if (_level)
                _level->draw(delta);

            DrawFPS(30, 65);
        EndDrawing();
    }
}
