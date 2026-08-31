#include "player.h"
#include "raylib.h"
#include "raymath.h"
#include "config.h"

const inline int PIXELS_PER_METER{50};
// Meters per second
const inline float PLAYER_SPEED{10.f};

void Player::handleEvent() { }

void Player::tick() {
  handleMovement();
  gun->tick();

  lastFrameTime += GetFrameTime();
}

void Player::update() {
  if (lastFrameTime >= 0.08f) {
    animationFrame = (animationFrame + 1) % textureIndex();
    lastFrameTime -= 0.08f; // if it's 0.09, we don't want to lose the 0.01
  }

  Rectangle srcrec = {
    animationFrame * PLAYER_TILE_SIZE,
    0,
    (Facing == RIGHT) ? PLAYER_TILE_SIZE : -PLAYER_TILE_SIZE,
    PLAYER_TILE_SIZE
  };
  Rectangle dstrec = {
    position.x,
    position.y,
    (Facing == RIGHT) ? PLAYER_TILE_SIZE : -PLAYER_TILE_SIZE,
    PLAYER_TILE_SIZE,
  };

  DrawTexturePro(textureToRender(), srcrec, dstrec, {0, 0}, 0, WHITE);
  gun->update();
}

void Player::handleMovement() {
  Vector2 direction{0, 0};
  if (IsKeyDown(KEY_W)) { direction.y -= 1; }
  if (IsKeyDown(KEY_S)) { direction.y += 1; }
  if (IsKeyDown(KEY_A)) { direction.x -= 1; }
  if (IsKeyDown(KEY_D)) { direction.x += 1; }
  direction = Vector2Normalize(direction);

  float speed = PLAYER_SPEED * PIXELS_PER_METER * GetFrameTime();
  position.x += direction.x * speed;
  position.y += direction.y * speed;

  if (direction.x > 0) {
    Facing = RIGHT; 
  } else if (direction.x < 0) {
    Facing = LEFT; 
  }

  State = (Vector2Length(direction) > 0) ? RUN : IDLE;
}

void Player::handleWallCollision() {
}

Texture2D Player::textureToRender() {
  switch(State) {
  case IDLE:
    return idleTexture;
  case RUN:
    return runTexture;
  }
}

int Player::textureIndex() {
  switch(State) {
  case IDLE:
    return 8;
  case RUN:
    return 6;
  }
}
