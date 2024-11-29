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
