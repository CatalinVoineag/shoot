#pragma once
#include <optional>
#include <raylib.h>
#include "engine/ecs/component.h"
#include "engine/eventBus.h"
#include "engine/ecs/entity.h"

class Gun;

class Bullet : public Entity {
  enum state { RELOAD, IDLE, FIRE };
  enum facing { RIGHT, LEFT };
  public:
  Bullet(Entity *owner);
  void tick();
  void update();
  void handleEvent();
  void handleMovement();
  void handleKeyPress();

  void unload() {
    UnloadTexture(bulletTexture);
  };

  private:
  Texture2D bulletTexture = LoadTexture("assets/guns/ar/bullet.png");
  std::optional<float>x;
  std::optional<float>y;
  float lastFrameTime = 0.f;
  state State = FIRE;
  facing Facing;
  Gun* gun;
};
