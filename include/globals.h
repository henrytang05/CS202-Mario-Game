#ifndef GLOBAL_H
#define GLOBAL_H

const int screenWidth = 1440;
const int screenHeight = 810;
const float ground = 3.0 * screenHeight / 4;
const int tilewidth = 16;
const int tileheight = 16;
#define ASSERT(condition) assert((condition) && "Assertion failed: " #condition)

#endif // !GLOBAL_H
