#include "raylib.h"

int main() {
  // test raylib
  // Create a window
  InitWindow(800, 600, "Hello, World!");
  SetTargetFPS(60);

  // Main game loop
  while (!WindowShouldClose()) {
    // begin drawing
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Hello, World!", 10, 10, 20, DARKGRAY);
    EndDrawing();
  }

  return 0;
}
