#pragma once
#include <memory>
#include <vector>
#include "player.h"
#include "raylib.h"
#include "engine/eventBus.h"

class GameScene {
  public:
  GameScene() : player(std::make_shared<Player>()) { }

  void tick();
  void handleEvent();
  void update();
  void render();
  void unload() {
    UnloadTexture(terrainTileset);
    player->unload();
  };

  private:
  std::shared_ptr<Player> player;
  Texture2D terrainTileset = LoadTexture("assets/terrain_tileset.png");
  EventBus* bus = EventBus::getInstance();
  std::vector<Vector2> pixelMap;

  void checkCollisions();
};
