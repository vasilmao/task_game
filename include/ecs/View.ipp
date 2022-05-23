template <typename ComponentT>
View<ComponentT>::Iterator::Iterator(EntityMapIterator iterator, EntityRegistry& registry)
    : iterator_{iterator},
      registry_{registry} {
}

template <typename ComponentT>
typename View<ComponentT>::Iterator& View<ComponentT>::Iterator::operator++() {
  ++iterator_;
  return *this;
}

template <typename ComponentT>
typename View<ComponentT>::Iterator View<ComponentT>::Iterator::operator++(int) {
  Iterator temp{*this};
  ++(*this);
  return temp;
}

template <typename ComponentT>
ComponentT* View<ComponentT>::Iterator::GetComponent() const {
  ComponentHolder<ComponentT>* holder = reinterpret_cast<ComponentHolder<ComponentT>*>(iterator_->second);
  assert(holder != nullptr);
  return holder->Get();
}

template <typename ComponentT>
EntityHandle View<ComponentT>::Iterator::GetEntityHandle() const {
  return EntityHandle{iterator_->first, registry_};
}

template <typename ComponentT>
View<ComponentT>::View(EntityMap& entity_map, EntityRegistry& registry) 
    : entity_map_{entity_map},
      registry_{registry} {
}

template <typename ComponentT>
typename View<ComponentT>::Iterator View<ComponentT>::begin() {
  return Iterator{entity_map_.begin(), registry_}; 
}

template <typename ComponentT>
typename View<ComponentT>::Iterator View<ComponentT>::end() {
  return Iterator{entity_map_.end(), registry_};
}
