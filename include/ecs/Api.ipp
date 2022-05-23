#pragma once

template <typename ComponentT>
View<ComponentT> GetView(EntityRegistry& registry) {
  return View<ComponentT>{registry.GetEntityMap<ComponentT>(), registry};
}
