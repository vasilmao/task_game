#pragma once

#include "Vector.hpp"
#include "ecs/Api.hpp"
#include "event_system/Events.hpp"
#include "Scene.hpp"

class EnemySpawner {
 public:
  EnemySpawner(Scene& scene, EntityRegistry& registry, const Vector2& field_size) : scene_{scene}, registry_{registry}, field_size_{field_size} {}
  void TrySpawn(const TimeEvent& event);
 private :
  Scene& scene_;
  EntityRegistry& registry_;
  Vector2 field_size_;
  const float spawn_delay_ = 7.0f;
  float time_from_last_spawn = 0.0f;
};

EntityHandle CreatePlayer(EntityRegistry& registry, const Vector2& pos, float r);
EntityHandle CreateStrangeEnemy(EntityRegistry& registry, const Vector2& pos, float r, const Vector2& speed);