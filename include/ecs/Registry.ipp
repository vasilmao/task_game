template <typename ComponentT, typename... Args>
void EntityRegistry::AddComponent(EntityId id, Args&&... args) {
  ComponentTypeId component_type_id = ComponentHolder<ComponentT>::GetTypeId();

  assert(entities_.find(id) != entities_.end());
  assert(components_[component_type_id].find(id) == components_[component_type_id].end());

  IComponentHolder* component_holder = new ComponentHolder<ComponentT>(std::forward<Args>(args)...);

  entities_[id].emplace(component_type_id, component_holder);
  components_[component_type_id].emplace(id, component_holder);
}

template <typename ComponentT>
void EntityRegistry::RemoveComponent(EntityId id) {
  ComponentTypeId component_type_id = ComponentHolder<ComponentT>::GetTypeId();

  assert(entities_.find(id) != entities_.end());
  assert(components_[component_type_id].find(id) != components_[component_type_id].end());

  components_[component_type_id].erase(id);
  IComponentHolder* component_to_remove_holder = entities_[id].find(component_type_id)->second;
  entities_[id].erase(component_type_id);

  delete component_to_remove_holder;
}

template <typename ComponentT>
ComponentT* EntityRegistry::GetComponent(EntityId id) {
  ComponentTypeId component_type_id = ComponentHolder<ComponentT>::GetTypeId();

  auto component_holder_iter = components_[component_type_id].find(id);

  if (component_holder_iter == components_[component_type_id].end()) {
    return nullptr;
  }

  return reinterpret_cast<ComponentHolder<ComponentT>*>(component_holder_iter->second)->Get();
}

template <typename ComponentT>
bool EntityRegistry::HasComponent(EntityId id) {
  ComponentTypeId component_type_id = ComponentHolder<ComponentT>::GetTypeId();

  auto component_holder_iter = components_[component_type_id].find(id);

  return component_holder_iter != components_[component_type_id].end();
}

template <typename ComponentT>
EntityMap& EntityRegistry::GetEntityMap() {
  ComponentTypeId component_type_id = ComponentHolder<ComponentT>::GetTypeId();

  return components_[component_type_id];
}
