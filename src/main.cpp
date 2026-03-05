#include "raylib.h"
int main() {
    InitWindow(800, 450, "Raylib OOP src/ directory test");
    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
