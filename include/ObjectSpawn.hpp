#pragma once

#include "ecs/Api.hpp"
#include "Vector.hpp"

EntityHandle CreatePlayer(EntityRegistry& registry, const Vector2& pos, float r);
EntityHandle CreateStrangeEnemy(EntityRegistry& registry, const Vector2& pos, float r, const Vector2& speed);