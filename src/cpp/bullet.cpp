#include "bullet.h"
#include "raylib.h"
#include "config.h"
#include "gun.h"

Bullet::Bullet(Entity *owner) : Entity(owner), gun(static_cast<Gun *>(owner)) {}

void Bullet::tick() {
  if(State != FIRE) { return; }

  if (x > GetScreenWidth()) { State = IDLE; } 

  x.value() += BULLET_SPEED * PIXELS_PER_METER * GetFrameTime(); 
}

void Bullet::update() {
  if (State == FIRE) {
    if (!x.has_value() && !y.has_value()) {
      x = gun->getPosition().x + 50;
      y = gun->getPosition().y + 80;
    };
    DrawTextureEx(bulletTexture, {x.value(), y.value()}, 0, 2.f, WHITE);
  }
}

void Bullet::handleEvent() { }
