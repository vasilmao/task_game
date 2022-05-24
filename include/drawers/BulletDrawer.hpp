#pragma once

#include "ecs/Api.hpp"
#include "Renderer.hpp"

class DefaultBulletDrawer {
  public:
    DefaultBulletDrawer(EntityHandle bullet) : bullet_{bullet} {}
    void Render(Renderer& renderer);
  private:
    EntityHandle bullet_;
};