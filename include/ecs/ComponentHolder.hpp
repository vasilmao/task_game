#pragma once

#include <cstdint>
#include <utility>

#include "ecs/Generator.hpp"

using ComponentTypeId = uint64_t;
using ComponentTypeIdGenerator = StaticIdGenerator<ComponentTypeId>;

class IComponentHolder {
 public:
  virtual ~IComponentHolder() = default;
};

template <typename ComponentT>
class ComponentHolderBase : public IComponentHolder {
 public:
  template <typename... Args>
  ComponentHolderBase(Args&&... args);

  ~ComponentHolderBase() override = default;

 protected:
  ComponentT component_;
};

template <typename ComponentT>
class ComponentHolder : public ComponentHolderBase<ComponentT> {
 public:
  template <typename... Args>
  ComponentHolder(Args&&... args);

  ComponentT* Get();

  static ComponentTypeId GetTypeId();

 private:
  static ComponentTypeId type_id_;
};

#include "ecs/ComponentHolder.ipp"
