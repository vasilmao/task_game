#pragma once

#include "ecs/ComponentHolder.hpp"
#include "ecs/Generator.hpp"

#include <cassert>
#include <cstdint>
#include <unordered_map>

using EntityId = uint64_t;

constexpr EntityId kInvalidEntityId = 0;

using EntityIdGenerator = IdGenerator<EntityId>;

using EntityMap = std::unordered_map<EntityId, IComponentHolder*>;
using ComponentMap = std::unordered_map<ComponentTypeId, IComponentHolder*>;

class EntityRegistry {
 public:
  EntityId CreateEntity();

  void DestroyEntity(EntityId id);

  void DestroyAllEntities();

  template <typename ComponentT, typename... Args>
  void AddComponent(EntityId id, Args&&... args);

  template <typename ComponentT>
  void RemoveComponent(EntityId id);

  template <typename ComponentT>
  ComponentT* GetComponent(EntityId id);

  template <typename ComponentT>
  bool HasComponent(EntityId id);

  template <typename ComponentT>
  EntityMap& GetEntityMap();

 private:
  using EntityStorage = std::unordered_map<EntityId, ComponentMap>;
  using ComponentStorage = std::unordered_map<ComponentTypeId, EntityMap>;

 private:
  EntityStorage entities_;
  ComponentStorage components_;
  EntityIdGenerator entity_id_generator_;
};

#include "ecs/Registry.ipp"
