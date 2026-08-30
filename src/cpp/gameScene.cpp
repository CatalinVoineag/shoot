#include "gameScene.h"
#include "config.h"
#include <memory>
#include <raylib.h>

void GameScene::tick () {
  // checkCollisions();
  player->tick();
};

void GameScene::update() {
}

void GameScene::handleEvent() {
  player->handleEvent();
}

void GameScene::sendEvents() { }

void GameScene::checkCollisions() {
}


void GameScene::render() {
  for(float i = 0.0f; i < GetScreenWidth(); i += TERRAIN_TILE_SIZE) {
    for(float y = 0.0f; y < GetScreenHeight(); y += TERRAIN_TILE_SIZE) {
      float tilePos;
      if (i == 0)      tilePos = 0.0f;
      else if ((i + TERRAIN_TILE_SIZE) >= GetScreenWidth()) tilePos = 160.0f;
      else             tilePos = 32.0f;

      float yTilePos = 32.0f;
      DrawTextureRec(terrainTileset, Rectangle{tilePos, yTilePos, TERRAIN_TILE_SIZE,TERRAIN_TILE_SIZE}, Vector2{i, y}, WHITE);
      // Refine this later      
    }
  }

  player->update();
}
