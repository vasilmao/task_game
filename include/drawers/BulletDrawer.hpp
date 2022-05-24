#pragma once

#include "Renderer.hpp"
#include "ecs/Api.hpp"

class DefaultBulletDrawer {
 public:
  DefaultBulletDrawer(EntityHandle bullet) : bullet_{bullet} {}
  void Render(Renderer& renderer);

 private:
  EntityHandle bullet_;
};