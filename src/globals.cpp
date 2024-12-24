#include "globals.h"

float MUSIC_VOLUME = 1.0f;
float SOUND_VOLUME = 1.0f;

bool isMario = true;

int globalNewCount(bool inc) {
  static int count = 0;
  if (inc)
    count++;
  return count;
}

int globalDeleteCount(bool inc) {
  static int count = 0;
  if (inc)
    count++;
  return count;
}

void *operator new(size_t size) {
  globalNewCount();
  return malloc(size);
}

void operator delete(void *ptr) noexcept {
  globalDeleteCount();
  free(ptr);
}
