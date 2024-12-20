#ifndef GLOBAL_H
#define GLOBAL_H

const int screenWidth = 1440;
const int gameWidth = 2624;
const int screenHeight = 810;

const int GAMEPLAY_TEXT_SIZE = 35;

extern float MUSIC_VOLUME;
extern float SOUND_VOLUME;

#define ASSERT(condition) assert((condition) && "Assertion failed: " #condition)

#endif // !GLOBAL_H
