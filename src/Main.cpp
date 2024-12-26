#include "Game.h"
#include "Interface.h"
#include "globals.h"

int main() {
  int retVal = 0;
  Game game;
  game.run();

  ASSERT(globalDeleteCount() == globalNewCount(), "Memory leak detected");
  return 0;
}
