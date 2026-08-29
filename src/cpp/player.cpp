#include "player.h"
#include "raylib.h"

const inline int PIXELS_PER_METER{50};
// Meters per second
const inline float PLAYER_SPEED{10.f};

void Player::handleEvent() {
  // auto wall = std::static_pointer_cast<Wall>(bus->getFront().data);
  // if (bus->getFront().event == WALL_COLLISION) {
  //   handleWallCollision(wall);
  // }
}

void Player::tick() {
  handleMovement();
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
}

void Player::handleMovement() {
  if (IsKeyDown(KEY_A)) { directions.emplace_back(KEY_A); }
  if (IsKeyDown(KEY_D)) { directions.emplace_back(KEY_D); }
  if (IsKeyDown(KEY_W)) { directions.emplace_back(KEY_W); }
  if (IsKeyDown(KEY_S)) { directions.emplace_back(KEY_S); }

  if (directions.size() > 0) {
    State = RUN;
    if (directions.back() == KEY_W && IsKeyDown(directions.back())) {
      position.y -= PLAYER_SPEED * PIXELS_PER_METER * GetFrameTime();
    } else if (directions.back() == KEY_S && IsKeyDown(directions.back())) {
      position.y += PLAYER_SPEED * PIXELS_PER_METER * GetFrameTime();
    } else if (directions.back() == KEY_A && IsKeyDown(directions.back())) {
      position.x -= PLAYER_SPEED * PIXELS_PER_METER * GetFrameTime();
      Facing = LEFT;
    } else if (directions.back() == KEY_D && IsKeyDown(directions.back())) {
      position.x += PLAYER_SPEED * PIXELS_PER_METER * GetFrameTime();
      Facing = RIGHT;
    } else {
      State = IDDLE;
      directions.pop_back();
    }
  }
}

void Player::handleWallCollision() {
}

Texture2D Player::textureToRender() {
  switch(State) {
  case Player::IDDLE:
    return idleTexture;
  case Player::RUN:
    return runTexture;
  }
}

int Player::textureIndex() {
  switch(State) {
  case Player::IDDLE:
    return 8;
  case Player::RUN:
    return 6;
  }
}
