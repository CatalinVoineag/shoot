#pragma once
#include "engine/ecs/component.h"
#include <concepts>
#include <memory>
#include <utility>
#include <vector>

using ComponentPtr = std::unique_ptr<Component>;
using ComponentPtrs = std::vector<ComponentPtr>;

class Entity {
  public:
  virtual void handleEvent() {
    for (ComponentPtr& component : Components) {
      component->handleEvent();
    }
  };
  virtual void tick() {
    for (ComponentPtr& component : Components) {
      component->tick();
    }
  };
  virtual void render() {
    for (ComponentPtr& component : Components) {
      component->tick();
    }
  };
  virtual void drawDebug() {
    for (ComponentPtr& component : Components) {
      component->tick();
    }
  };

  template<typename CType, typename... CArgs>
  requires std::derived_from<CType, Component>
  CType* addComponent(CArgs&&... constructorArgs) {
    std::unique_ptr<CType> NewComponent{
      std::make_unique<CType>(this, std::forward<CArgs>(constructorArgs)...)
    };
    CType* RawPtr{NewComponent.get()};
    Components.emplace_back(std::move(NewComponent));
    RawPtr->initialize();
    return RawPtr;
  }

  private:
  ComponentPtrs Components;
};
