#pragma once

#include "ecs/Registry.hpp"

class EntityHandle {
 public:
  EntityHandle(EntityId id, EntityRegistry& registry);
  EntityHandle(const EntityHandle& other) : id_(other.id_), registry_(other.registry_) {}

  EntityHandle& operator=(const EntityHandle& other);

  void Destroy();

  template <typename ComponentT, typename... Args>
  void AddComponent(Args&&... args);

  template <typename ComponentTy>
  void RemoveComponent();

  template <typename ComponentT>
  ComponentT* GetComponent();

  template <typename ComponentT>
  bool HasComponent();

 private:
  EntityId id_{kInvalidEntityId};
  EntityRegistry& registry_;
};

#include "ecs/EntityHandle.ipp"
