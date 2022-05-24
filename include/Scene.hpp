#pragma once

#include <list>

#include "ecs/EntityHandle.hpp"

class Scene {
 public:
  Scene(EntityRegistry& registry);
  void AddEntity(const EntityHandle& handle);
  std::list<EntityHandle>& GetEntities();
  ~Scene();
 private:
  EntityRegistry& registry_;
  // EntityHandle player_;
  // std::list<EntityHandle> enemies_;
  // std::list<EntityHandle> bullets_;
  // std::list<EntityHandle> pickable_items_;

  std::list<EntityHandle> entities_;

};