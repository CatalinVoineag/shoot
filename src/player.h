#pragma once
#include <memory>
#include <raylib.h>
#include "engine/eventBus.h"
#include "gun.h"

class Player {
  enum state { IDLE, RUN };

  public:
  enum facing { LEFT, RIGHT, UP, DOWN };
  Player() : gun(std::make_shared<Gun>(this)) {}
  void tick();
  void update();
  void handleEvent();
  void handleMovement();

  void unload() {
    UnloadTexture(idleTexture);
    UnloadTexture(runTexture);
    gun->unload();
  }

  Vector2 getPosition() {
    return position;
  }

  facing getFacing() {
    return Facing;
  }

  private:
  Texture2D idleTexture = LoadTexture("assets/player_idle.png");
  Texture2D runTexture = LoadTexture("assets/player_run.png");
  void handleWallCollision();
  facing Facing = RIGHT;
  state State = IDLE;
  Vector2 position { 200, 300 };
  float lastFrameTime = 0.f;
  int animationFrame = 0;
  EventBus* bus = EventBus::getInstance();
  std::shared_ptr<Gun> gun;

  Texture2D textureToRender();
  int textureIndex();
};

