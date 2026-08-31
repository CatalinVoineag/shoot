#pragma once

class Entity;

class Component {
  public:
  Component(Entity* Owner) : Owner(Owner) {}
  virtual void initialize() {}
  virtual void handleEvent() {};
  virtual void tick() {};
  virtual void render() {};
  virtual void drawDebug() {};
  Entity* getOwner() { return Owner; }


  private:
  Entity* Owner{nullptr};
};
