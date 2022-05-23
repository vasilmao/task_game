#pragma once

template <typename ComponentT, typename... Args>
void EntityHandle::AddComponent(Args&&... args) {
  registry_.AddComponent<ComponentT>(id_, std::forward<Args>(args)...);
}

template <typename ComponentT>
void EntityHandle::RemoveComponent() {
  registry_.RemoveComponent<ComponentT>(id_);
}

template <typename ComponentT>
ComponentT* EntityHandle::GetComponent() {
  return registry_.GetComponent<ComponentT>(id_);
}

template <typename ComponentT>
bool EntityHandle::HasComponent() {
  return registry_.HasComponent<ComponentT>(id_);
}
