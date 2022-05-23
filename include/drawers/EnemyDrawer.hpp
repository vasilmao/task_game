#pragma once

#include "ecs/Api.hpp"
#include "Renderer.hpp"

class StrangeEnemyDrawer {
  public:
    StrangeEnemyDrawer(EntityHandle& enemy_handle, float r) : enemy_(enemy_handle), r_{r} {}
    void Render(Renderer& renderer);
  private:
    EntityHandle enemy_;
    float r_;
};