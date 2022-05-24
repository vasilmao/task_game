#pragma once

#include <unordered_map>

#include "ecs/EntityHandle.hpp"
#include "ecs/Registry.hpp"

template <typename ComponentT>
class View {
 public:
  class Iterator {
   private:
    using EntityMapIterator = typename std::unordered_map<EntityId, IComponentHolder*>::iterator;

   public:
    Iterator(EntityMapIterator iterator, EntityRegistry& registry);

    Iterator& operator++();
    Iterator operator++(int unused);

    ComponentT* GetComponent() const;
    EntityHandle GetEntityHandle() const;

   public:
    friend bool operator==(const Iterator& lhs, const Iterator& rhs) { return lhs.iterator_ == rhs.iterator_; }

    friend bool operator!=(const Iterator& lhs, const Iterator& rhs) { return lhs.iterator_ != rhs.iterator_; }

    friend std::pair<EntityHandle, ComponentT*> operator*(const Iterator& it) {
      return std::pair<EntityHandle, ComponentT*>(it.GetEntityHandle(), it.GetComponent());
    }

   private:
    EntityMapIterator iterator_;
    EntityRegistry& registry_;
  };

 public:
  View(EntityMap& entity_map, EntityRegistry& registry);

  Iterator begin();

  Iterator end();

 private:
  EntityMap& entity_map_;
  EntityRegistry& registry_;
};

#include "ecs/View.ipp"
