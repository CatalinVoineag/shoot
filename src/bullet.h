#pragma once
#include <raylib.h>
#include "engine/ecs/component.h"
#include "engine/eventBus.h"

class Bullet {
  enum state { RELOAD, IDLE, FIRE };
  public:
  Bullet() {};
  void tick();
  void update();
  void handleEvent();
  void handleMovement();
  void handleKeyPress();

  void fire() { State = FIRE; };

  void unload() {
    UnloadTexture(bulletTexture);
  };

  private:
  Texture2D bulletTexture = LoadTexture("assets/guns/ar/bullet.png");
  float x = 100;
  float y = 200;
  float lastFrameTime = 0.f;
  state State = IDLE;
 
};
