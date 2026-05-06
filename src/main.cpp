#include <iostream>
#include "raylib.h"

int main() {
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    const char* SCREEN_TITLE = "Dungeons";

    // Create a window.
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_TITLE);
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(SKYBLUE);
        DrawText("Dungeons", 20, 20, 30, BLACK);
        DrawFPS(20, 55);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
