#ifndef GLOBAL_H
#define GLOBAL_H

const int screenWidth = 1440;
const int gameWidth = 2624;
const int screenHeight = 810;

const int GAMEPLAY_TEXT_SIZE = 35;

extern float MUSIC_VOLUME;
extern float SOUND_VOLUME;

int globalNewCount(bool inc = false);
int globalDeleteCount(bool inc = false);

void *operator new(size_t size);
void operator delete(void *ptr) noexcept;

extern bool isMario;
#define ASSERT(condition) assert((condition) && "Assertion failed: " #condition)

template <typename Base, typename T> inline bool instanceof(const T *ptr) {
  return dynamic_cast<const Base *>(ptr) != nullptr;
}

#endif // !GLOBAL_H
