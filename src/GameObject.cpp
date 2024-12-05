#include "GameObject.h"
void Block::Render() {
    DrawTexture(texture, position.x, position.y, WHITE);
}

void Interact::Render() {
    DrawTexture(texture, position.x, position.y, WHITE);
}
