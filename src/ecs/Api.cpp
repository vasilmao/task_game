#include "ecs/Api.hpp"

EntityHandle CreateEntity(EntityRegistry& registry) {
  return EntityHandle{registry.CreateEntity(), registry};
}
