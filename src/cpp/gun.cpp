#include "gun.h"
#include "raylib.h"

void Gun::handleEvent() { }

void Gun::tick() {
  handleKeyPress();
}

void Gun::update() {
  DrawTextureRec(idleTexture, Rectangle{0, 0, 362, 145}, Vector2{100, 100}, WHITE);
}

void Gun::handleMovement() {
}

void Gun::handleWallCollision() {
}

void Gun::handleKeyPress() {
  if (IsKeyPressed(KEY_SPACE)) { PlaySound(fireSound); }
}

