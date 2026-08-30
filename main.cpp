#include "raylib.h"
#include "gameScene.h"
#include "engine/eventBus.h"

EventBus* EventBus::instancePtr = nullptr;
std::mutex EventBus::mtx;

int main(void) {
  EventBus* bus = EventBus::getInstance();

  InitWindow(800, 550, "Shoot");
  GameScene gameScene = GameScene();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    gameScene.sendEvents();
    gameScene.tick(); 
    while (bus->size() > 0) {
      gameScene.handleEvent();
      bus->pop();
    }
    gameScene.render(); 

    DrawFPS(100, 100);

    EndDrawing();
  }

  gameScene.unload();
  CloseWindow();
  return 0;
}

