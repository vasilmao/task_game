#pragma once

#include "ecs/EntityHandle.hpp"
#include "ecs/Registry.hpp"
#include "ecs/View.hpp"

EntityHandle CreateEntity(EntityRegistry& registry);

template <typename ComponentT>
View<ComponentT> GetView(EntityRegistry& registry);

#include "ecs/Api.ipp"
