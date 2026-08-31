#include "gun.h"
#include "player.h"
#include "raylib.h"

void Gun::handleEvent() { }

void Gun::tick() {
  handleKeyPress();
}

void Gun::update() {
  Rectangle srcrec = {
    0, 0,
    (player->getFacing() == Player::RIGHT) ? width : -width,
    height
  };
  Rectangle dstrec = {
    gunPosition(player).x,
    gunPosition(player).y,
    (player->getFacing() == Player::RIGHT) ? width : -width,
    height,
  };

  DrawTexturePro(idleTexture, srcrec, dstrec, {0, 0}, 0, WHITE);
}

void Gun::handleMovement() {
}

void Gun::handleWallCollision() {
}

void Gun::handleKeyPress() {
  if (IsKeyPressed(KEY_SPACE)) { PlaySound(fireSound); }
}

Rectangle Gun::gunPosition(Player* player) {
  Rectangle rect{};

  if (player->getFacing() == Player::RIGHT) {
    rect.x = player->getPosition().x + 100;
    rect.y = player->getPosition().y + 80;
  } else {
    rect.x = player->getPosition().x - 35;
    rect.y = player->getPosition().y + 80;
  }

  return rect;
}

