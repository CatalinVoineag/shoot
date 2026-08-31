#include "gun.h"
#include "player.h"
#include "raylib.h"

void Gun::handleEvent() { }

void Gun::tick() {
  handleKeyPress();

  lastFrameTime += GetFrameTime();
}

void Gun::update() {
  if (lastFrameTime >= 0.012f) {
    animationFrame = (animationFrame + 1) % textureIndex();
    casingAnimationFrame = (casingAnimationFrame + 1) % casingFrames;
    lastFrameTime -= 0.012f;
  }

  Rectangle srcrec = {
    animationFrame * width, 0,
    (player->getFacing() == Player::RIGHT) ? width : -width,
    height
  };
  Rectangle dstrec = {
    gunPosition(player).x,
    gunPosition(player).y,
    (player->getFacing() == Player::RIGHT) ? width : -width,
    height,
  };

  DrawTexturePro(texture(), srcrec, dstrec, {0, 0}, 0, WHITE);
  if (State == FIRE) {
    // muzzle flash
    srcrec = {
      animationFrame * width, 0,
      (player->getFacing() == Player::RIGHT) ? width : -width,
      height
    };
    dstrec = {
      gunPosition(player).x - 5,
      gunPosition(player).y,
      (player->getFacing() == Player::RIGHT) ? width : -width,
      height,
    };

    DrawTexturePro(fireFxTexture, srcrec, dstrec, {0, 0}, 0, WHITE);

    // bullet casing
    srcrec = {
      casingAnimationFrame * width, 0,
      (player->getFacing() == Player::RIGHT) ? width : -width,
      height
    };
    dstrec = {
      gunPosition(player).x,
      gunPosition(player).y,
      (player->getFacing() == Player::RIGHT) ? width : -width,
      height,
    };

    DrawTexturePro(casingFxTexture, srcrec, dstrec, {0, 0}, 0, WHITE);
  }
}

void Gun::handleMovement() {
}

void Gun::handleWallCollision() {
}

void Gun::handleKeyPress() {
  if (IsKeyPressed(KEY_SPACE)) { 
    PlaySound(fireSound);
    State = FIRE;
  } else if (endAnimation()) {
    State = IDLE;
  }
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

Texture2D Gun::texture() {
  switch(State) {
    case IDLE:
      return idleTexture;
    case FIRE:
      return singleFireTexture;
  }
}

int Gun::textureIndex() {
  switch(State) {
    case IDLE:
      return 1;
    case FIRE:
      return 16;
  }
}

bool Gun::endAnimation() {
  return !IsKeyPressed(KEY_SPACE) &&
    animationFrame == textureIndex() - 1 &&
    casingAnimationFrame == casingFrames - 1;
}
