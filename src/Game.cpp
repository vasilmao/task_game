#include "Engine.h"
#include "Scene.hpp"
#include "ecs/Api.hpp"
#include "Components.hpp"
#include "drawers/Drawers.hpp"
#include "collision/CollisionManager.hpp"
#include "collision/CollisionResponce.hpp"

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <iostream>

//
//  You are free to modify this file
//

//  is_key_pressed(int button_vk_code) - check if a key is pressed,
//                                       use keycodes (VK_SPACE, VK_RIGHT, VK_LEFT, VK_UP, VK_DOWN, VK_RETURN)
//
//  get_cursor_x(), get_cursor_y() - get mouse cursor position
//  is_mouse_button_pressed(int button) - check if mouse button is pressed (0 - left button, 1 - right button)
//  schedule_quit_game() - quit game after act()

Scene* scene = nullptr;
Renderer* renderer = nullptr;
EntityRegistry registry{};
CollisionManager manager{};
CollisionResponcer responcer{};

void AddWalls();

// initialize game data in this function
void initialize()
{
  renderer = new Renderer{reinterpret_cast<uint32_t*>(buffer), SCREEN_WIDTH, SCREEN_HEIGHT};
  scene = new Scene{registry};
  EntityHandle player = CreateEntity(registry);

  Vector2 player_start_pos{100, 100};
  float player_radius = 20.0f;

  player.AddComponent<Health>(100, 100);
  player.AddComponent<RenderComponent>(std::bind(&PlayerDrawer::Render, PlayerDrawer{player, player_radius}, std::placeholders::_1));
  player.AddComponent<Transform>(player_start_pos, 0.0f);
  player.AddComponent<CollisionShape>(new CollisionCircle{player_start_pos, player_radius});
  player.AddComponent<Speed>(Vector2{0, 0});
  player.AddComponent<EntityTypeComponent>(PLAYER);

  scene->AddEntity(player);

  EntityHandle enemy = CreateEntity(registry);
  enemy.AddComponent<Health>(100, 100);
  enemy.AddComponent<RenderComponent>(std::bind(&StrangeEnemyDrawer::Render, StrangeEnemyDrawer{enemy, player_radius}, std::placeholders::_1));
  enemy.AddComponent<Transform>(Vector2{300, 300}, 0.0f);
  enemy.AddComponent<CollisionShape>(new CollisionCircle{Vector2{300, 300}, player_radius});
  enemy.AddComponent<Speed>(Vector2{400, 400});
  enemy.AddComponent<EntityTypeComponent>(ENEMY);

  scene->AddEntity(enemy);

  AddWalls();
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();
  
  std::list<EntityHandle>& entities = scene->GetEntities();
  for (auto it = entities.begin(); it != entities.end(); ++it) {
    if (it->HasComponent<Speed>() && it->HasComponent<Transform>()) {
      it->GetComponent<Transform>()->pos += (it->GetComponent<Speed>()->speed) * dt;
      if (it->HasComponent<CollisionShape>()) {
        ICollisionShape* shape = it->GetComponent<CollisionShape>()->form;
        if (shape->GetType() == COLLISION_CIRCLE) {
          dynamic_cast<CollisionCircle*>(shape)->UpdateCenter(it->GetComponent<Transform>()->pos);
        }
      }
    }
  }

  for (auto it1 = entities.begin(); it1 != entities.end(); ++it1) {
    auto it1_copy = it1;
    it1_copy++;
    for (auto it2 = it1_copy; it2 != entities.end(); ++it2) {
      if (manager.DetectCollision(dynamic_cast<ICollisionShape*>(it1->GetComponent<CollisionShape>()->form), dynamic_cast<ICollisionShape*>(it2->GetComponent<CollisionShape>()->form))) {
        responcer.ResponceCollision(*it1, *it2);
      }
    }
  }
}

// fill buffer in this function
// uint32_t buffer[SCREEN_HEIGHT][SCREEN_WIDTH] - is an array of 32-bit colors (8 bits per R, G, B)
void draw()
{
  // clear backbuffer
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
  std::list<EntityHandle>& entities = scene->GetEntities();
  for (auto it = entities.begin(); it != entities.end(); ++it) {
    if (it->HasComponent<RenderComponent>()) {
      it->GetComponent<RenderComponent>()->render(*renderer);
    }
  }
}

// free game data in this function
void finalize()
{
}

void AddWalls() {
  EntityHandle down_wall = CreateEntity(registry);
  down_wall.AddComponent<CollisionShape>(new CollisionWall{Vector2{0, SCREEN_HEIGHT}, Vector2{SCREEN_WIDTH, SCREEN_HEIGHT}});
  down_wall.AddComponent<EntityTypeComponent>(WALL);
  scene->AddEntity(down_wall);



  EntityHandle left_wall = CreateEntity(registry);
  left_wall.AddComponent<CollisionShape>(new CollisionWall{Vector2{0, 0}, Vector2{0, SCREEN_HEIGHT}});
  left_wall.AddComponent<EntityTypeComponent>(WALL);
  scene->AddEntity(left_wall);

  EntityHandle right_wall = CreateEntity(registry);
  right_wall.AddComponent<CollisionShape>(new CollisionWall{Vector2{SCREEN_WIDTH, 0}, Vector2{SCREEN_WIDTH, SCREEN_HEIGHT}});
  right_wall.AddComponent<EntityTypeComponent>(WALL);
  scene->AddEntity(right_wall);

  EntityHandle up_wall = CreateEntity(registry);
  up_wall.AddComponent<CollisionShape>(new CollisionWall{Vector2{0, 0}, Vector2{SCREEN_WIDTH, 0}});
  up_wall.AddComponent<EntityTypeComponent>(WALL);
  scene->AddEntity(up_wall);

}