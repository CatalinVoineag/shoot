#pragma once
#include <raylib.h>
#include "engine/eventBus.h"

class Gun {
  public:
  enum facing { LEFT, RIGHT };
  enum state { RELOAD, IDDLE, SHOOT };
  void tick();
  void update();
  void handleEvent();
  void handleMovement();
  void handleKeyPress();

  void unload() {
    UnloadTexture(idleTexture);
    UnloadWave(fireWave);
    UnloadSound(fireSound);
  }

  Vector2 getPosition() {
    return position;
  }

  private:
  Texture2D idleTexture = LoadTexture("assets/assaultrifle.png");
  Wave fireWave = LoadWave("assets/sounds/556/single.wav");
  Sound fireSound = LoadSoundFromWave(fireWave);
  void handleWallCollision();
  facing Facing = RIGHT;
  state State = IDDLE;
  Vector2 position { 200, 300 };
  float lastFrameTime = 0.f;
  int animationFrame = 0;
  EventBus* bus = EventBus::getInstance();
};

