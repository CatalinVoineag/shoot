#pragma once
#include <raylib.h>
#include "engine/ecs/component.h"
#include "engine/eventBus.h"

class Player;

class Gun : public Component {
  public:
  enum facing { LEFT, RIGHT };
  enum state { RELOAD, IDLE, FIRE };
  Gun(Entity *owner);

  // Do we need these or can we rely on component tick?
  void tick();
  void update();
  void handleEvent();
  void handleMovement();
  void handleKeyPress();

  void unload() {
    UnloadTexture(idleTexture);
    UnloadTexture(singleFireTexture);
    UnloadTexture(fireFxTexture);
    UnloadTexture(casingFxTexture);
    UnloadWave(fireWave);
    UnloadSound(fireSound);
  }

  Vector2 getPosition() {
    return position;
  }

  private:
  Texture2D idleTexture = LoadTexture("assets/guns/ar/ar.png");
  Texture2D singleFireTexture = LoadTexture("assets/guns/ar/single_fire.png");
  Texture2D fireFxTexture = LoadTexture("assets/guns/ar/fire_fx.png");
  Texture2D casingFxTexture = LoadTexture("assets/guns/ar/casing.png");
  Wave fireWave = LoadWave("assets/sounds/556/single.wav");
  Sound fireSound = LoadSoundFromWave(fireWave);
  void handleWallCollision();
  facing Facing = RIGHT;
  state State = IDLE;
  Vector2 position { 200, 300 };
  float lastFrameTime = 0.f;
  int animationFrame = 0;
  int casingAnimationFrame = 0;
  int casingFrames = 24;
  EventBus* bus = EventBus::getInstance();
  Player* player;
  float width = 128.f; 
  float height = 48.f; 
  Rectangle gunPosition(Player* player);

  Texture2D texture();
  int textureIndex();
  bool endAnimation();
};
