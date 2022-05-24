#pragma once

#include "Vector.hpp"
#include "ecs/Api.hpp"

EntityHandle CreatePlayer(EntityRegistry& registry, const Vector2& pos, float r);
EntityHandle CreateStrangeEnemy(EntityRegistry& registry, const Vector2& pos, float r, const Vector2& speed);