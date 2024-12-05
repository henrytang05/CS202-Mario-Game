#include "Game.h"

void showErrorAndExit(const char *errMsg) {
	while (!WindowShouldClose()) {
		BeginDrawing();
			ClearBackground(BLACK);
			DrawText(errMsg, 20, 20, 20, RED);
		EndDrawing();
	}
	exit(EXIT_FAILURE);
}
int main() {
  int retVal = 0;
  Game game;
  try {
    game.run();
  }
  catch(std::logic_error &e) {
		showErrorAndExit(e.what());
		retVal = EXIT_FAILURE; 
	}
  return 0;
}

//Main function
// int main() {
//     InitWindow(800, 600, "Tilemap Renderer");
//     SetTargetFPS(60);

//     TileFactory factory("Map/OverWorld.json", "Map/OverWorld.png");
//     MapRenderer mapRenderer("Map/Level1.json", factory);
//     MyCamera camera;
//     while (!WindowShouldClose()) {
//         Vector2 playerPos = { 16.0f, 160.0f };
//         camera.Update(playerPos);

//         BeginDrawing();
//         ClearBackground(RAYWHITE);
//         camera.BeginMode();
//         mapRenderer.Render();
//         camera.EndMode();

//         EndDrawing();
//     }

//     CloseWindow();
//     return 0;
// }

// void showErrorAndExit(const char *errMsg) {
// 	while (!WindowShouldClose()) {
// 		BeginDrawing();
// 			ClearBackground(BLACK);
// 			DrawText(errMsg, 20, 20, 20, RED);
// 		EndDrawing();
// 	}
// 	exit(EXIT_FAILURE);
// }
// int main() {
//   int retVal = 0;
//   Game game;
//   try {
//     game.run();
//   }
//   catch(std::logic_error &e) {
// 		showErrorAndExit(e.what());
// 		retVal = EXIT_FAILURE; 
// 	}
//   return 0;
// }