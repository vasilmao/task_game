#include "ecs/Registry.hpp"

#include <iostream>

EntityId EntityRegistry::CreateEntity() {
  EntityId id = entity_id_generator_.Next();
  entities_.emplace(id, ComponentMap{});
  return id;
}

void EntityRegistry::DestroyEntity(EntityId id) {
  assert(entities_.find(id) != entities_.end());

  for (auto it = entities_[id].begin(); it != entities_[id].end(); ++it) {
    ComponentTypeId component_type_id = it->first;

    IComponentHolder* component_to_remove_holder = components_[component_type_id].find(id)->second;
    components_[component_type_id].erase(id);
    delete component_to_remove_holder;
  }

	entities_.erase(id);
}

void EntityRegistry::DestroyAllEntities() {
  for (auto iter = entities_.begin(); iter != entities_.end(); ++iter) {
    DestroyEntity(iter->first);
  }
}
