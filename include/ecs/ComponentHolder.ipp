template <typename ComponentT>
template <typename... Args>
ComponentHolderBase<ComponentT>::ComponentHolderBase(Args&&... args) 
    : component_{std::forward<Args>(args)...} {
}

template <typename ComponentT>
template <typename... Args>
ComponentHolder<ComponentT>::ComponentHolder(Args&&... args)
    : ComponentHolderBase<ComponentT>{std::forward<Args>(args)...} {
}

template <typename ComponentT>
ComponentT* ComponentHolder<ComponentT>::Get() {
  return &this->component_;
}

template <typename ComponentT>
ComponentTypeId ComponentHolder<ComponentT>::GetTypeId() {
  return type_id_;
}

template <typename ComponentT>
ComponentTypeId ComponentHolder<ComponentT>::type_id_{ComponentTypeIdGenerator::Next()};
