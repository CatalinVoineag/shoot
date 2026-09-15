#include "bullet.h"
#include "raylib.h"
#include "config.h"
#include "gun.h"
#include "player.h"

Bullet::Bullet(Entity *owner) : Entity(owner), gun(static_cast<Gun *>(owner)) {
  x = gun->getMuzzlePosition().x;
  y = gun->getMuzzlePosition().y;
  Facing = gun->getPlayer()->getFacing() == Player::RIGHT ? RIGHT : LEFT;

}

void Bullet::tick() {
  if(State != FIRE) { return; }

  if (x > GetScreenWidth() || x < 0) { State = IDLE; } 

  if (Facing == RIGHT) {
    x.value() += BULLET_SPEED * PIXELS_PER_METER * GetFrameTime(); 
  } else {
    x.value() -= BULLET_SPEED * PIXELS_PER_METER * GetFrameTime(); 
  }
}

void Bullet::update() {
  if (State == FIRE) {
    DrawTextureEx(bulletTexture, {x.value(), y.value()}, 0, 2.f, WHITE);
  }
}

void Bullet::handleEvent() { }
