#pragma once
#include <vector>
#include "raylib.h"
#include "engine/eventBus.h"

class GameScene {
  public:
  GameScene() { }

  void tick();
  void handleEvent();
  void update();
  void render();
  void unload() {
    // UnloadTexture(background);
    // UnloadTexture(levelBackground);
    // ship->unload();
  };

  private:
  Texture2D terrainTileset = LoadTexture("Assets/terrain_tileset.png");
  EventBus* bus = EventBus::getInstance();
  std::vector<Vector2> pixelMap;

  void checkCollisions();
};
