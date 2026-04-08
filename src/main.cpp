#include "raylib.h"
#include <iostream>
#include "test.h"
int main() {

    std::cout << test << std::endl;

    InitWindow(800, 450, "Raylib OOP");
    SetTargetFPS(60);


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
