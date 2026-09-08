#include "bullet.h"
#include "raylib.h"
#include "config.h"

void Bullet::tick() {
  if(State != FIRE) { return; }
  if (x > GetScreenWidth()) { State = IDLE; } 
  x += BULLET_SPEED * PIXELS_PER_METER * GetFrameTime(); 
}

void Bullet::update() {
  if (State == FIRE) {
    DrawTextureEx(bulletTexture, {x, y}, 0, 2.f, WHITE);
  }
}
