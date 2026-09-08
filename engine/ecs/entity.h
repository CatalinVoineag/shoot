#pragma once
#include "engine/ecs/component.h"
#include <concepts>
#include <memory>
#include <utility>
#include <vector>

using ComponentPtr = std::unique_ptr<Component>;
using ComponentPtrs = std::vector<ComponentPtr>;

using EntityPtr = std::unique_ptr<Entity>;
using EntityPtrs = std::vector<EntityPtr>;

class Entity {
  public:
  Entity(Entity* Owner = nullptr) : Owner(Owner) {}
  Entity* getOwner() { return Owner; }
  virtual void initialize() {}
  virtual ~Entity() = default;

  virtual void handleEvent() {
    for (ComponentPtr& component : Components) {
      component->handleEvent();
    }
    for (EntityPtr& entity : Entities) {
      entity->handleEvent();
    }
  };
  virtual void tick() {
    for (ComponentPtr& component : Components) {
      component->tick();
    }
    for (EntityPtr& entity : Entities) {
      entity->tick();
    }
  };
  virtual void render() {
    for (ComponentPtr& component : Components) {
      component->render();
    }
    for (EntityPtr& entity : Entities) {
      entity->render();
    }
  };
  virtual void drawDebug() {
    for (ComponentPtr& component : Components) {
      component->drawDebug();
    }
    for (EntityPtr& entity : Entities) {
      entity->drawDebug();
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

  template<typename EType, typename... EArgs>
  requires std::derived_from<EType, Entity>
  EType* addEntity(EArgs&&... constructorArgs) {
    std::unique_ptr<EType> NewEntity{
      std::make_unique<EType>(this, std::forward<EArgs>(constructorArgs)...)
    };
    EType* RawPtr{NewEntity.get()};
    Entities.emplace_back(std::move(NewEntity));
    RawPtr->initialize();
    return RawPtr;
  }

  private:
  ComponentPtrs Components;
  EntityPtrs Entities;
  Entity* Owner{nullptr};
};
