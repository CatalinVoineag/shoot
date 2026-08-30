#pragma once
#include <raylib.h>
#include <vector>
#include "engine/eventBus.h"
#include "config.h"

class Player {
  public:
  enum facing { LEFT, RIGHT, UP, DOWN };
  enum state { IDDLE, RUN };
  void tick();
  void update();
  void handleEvent();
  void handleMovement();

  void unload() {
    UnloadTexture(idleTexture);
    UnloadTexture(runTexture);
  }

  Vector2 getPosition() {
    return position;
  }

  private:
  Texture2D idleTexture = LoadTexture("assets/player_idle.png");
  Texture2D runTexture = LoadTexture("assets/player_run.png");
  void handleWallCollision();
  std::vector<int> directions;
  facing Facing = RIGHT;
  state State = IDDLE;
  Vector2 position { 200, 300 };
  float lastFrameTime = 0.f;
  int animationFrame = 0;
  EventBus* bus = EventBus::getInstance();

  Texture2D textureToRender();
  int textureIndex();
};

