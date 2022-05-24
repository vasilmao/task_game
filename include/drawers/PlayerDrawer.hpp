#pragma once

#include "Renderer.hpp"
#include "ecs/Api.hpp"

class PlayerDrawer {
 public:
  PlayerDrawer(EntityHandle& player_handler, float r) : player_(player_handler), r_{r} {}
  void Render(Renderer& renderer);

 private:
  EntityHandle player_;
  float r_;
};