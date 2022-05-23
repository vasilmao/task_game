#include "ecs/EntityHandle.hpp"

EntityHandle::EntityHandle(EntityId id, EntityRegistry& registry) : id_{id}, registry_{registry} {}

EntityHandle& EntityHandle::operator=(const EntityHandle& other) {
  id_ = other.id_;
  registry_ = other.registry_;
  return *this;
}

void EntityHandle::Destroy() { registry_.DestroyEntity(id_); }
