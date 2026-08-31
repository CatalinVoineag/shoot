#pragma once
#include <raylib.h>
#include "engine/eventBus.h"

class Player;

class Gun {
  public:
  enum facing { LEFT, RIGHT };
  enum state { RELOAD, IDDLE, SHOOT };
  Gun(Player* p) : player(p) {}
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
  Player* player;
  float width = 126.f; 
  float height = 48.f; 

  Rectangle gunPosition(Player* player);
};
