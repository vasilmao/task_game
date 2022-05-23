#include "Engine.h"
#include "Scene.hpp"
#include "ecs/Api.hpp"
#include "Components.hpp"
#include "drawers/Drawers.hpp"

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
  player.AddComponent<Transform>(Vector2{100, 100}, 0.0f);
  player.AddComponent<CollisionShape>(new CollisionCircle{player_start_pos, player_radius});

  scene->AddEntity(player);
}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();

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

