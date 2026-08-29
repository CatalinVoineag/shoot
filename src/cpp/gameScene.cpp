#include "gameScene.h"
#include <raylib.h>

void GameScene::tick () {
  // checkCollisions();
};

void GameScene::handleEvent() {
}

void GameScene::checkCollisions() {
}

void GameScene::render() {
  DrawTextureRec(terrainTileset, Rectangle{0, 0, 32,32}, Vector2{0, 0}, WHITE);
}
