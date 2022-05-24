#include "Engine.h"
#include "Scene.hpp"
#include "ecs/Api.hpp"
#include "Components.hpp"
#include "drawers/Drawers.hpp"
#include "collision/CollisionManager.hpp"
#include "collision/CollisionResponce.hpp"
#include "event_system/EventSystem.hpp"
#include "InputHandler.hpp"
#include "ObjectSpawn.hpp"
#include "PlayerEventHandler.hpp"

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
Dispatcher dispatcher{};
InputHandler* input_handler;
PlayerEventHandler* player_event_handler;


void AddWalls();
void CheckInput();
void RegisterCallback();

// initialize game data in this function
void initialize()
{
  input_handler = new InputHandler{dispatcher};
  renderer = new Renderer{reinterpret_cast<uint32_t*>(buffer), SCREEN_WIDTH, SCREEN_HEIGHT};
  scene = new Scene{registry};

  EntityHandle player = CreatePlayer(registry, {100, 100}, 20.0f);

  scene->AddEntity(player);

  player_event_handler = new PlayerEventHandler{player, 300};

  RegisterCallback();


  EntityHandle enemy = CreateStrangeEnemy(registry, {100, 100}, 20.0f, Vector2{200, 200});

  scene->AddEntity(enemy);

  AddWalls();


}

// this function is called to update game data,
// dt - time elapsed since the previous update (in seconds)
void act(float dt)
{
  std::cout << "check_input\n";
  CheckInput();

  std::cout << "act\n";
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
  std::cout << "collide\n";
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
  std::cout << "draw\n";
  memset(buffer, 0, SCREEN_HEIGHT * SCREEN_WIDTH * sizeof(uint32_t));
  std::list<EntityHandle>& entities = scene->GetEntities();
  for (auto it = entities.begin(); it != entities.end(); ++it) {
    if (it->HasComponent<RenderComponent>()) {
      it->GetComponent<RenderComponent>()->render(*renderer);
    }
  }
  std::cout << "draw complete\n";
}

// free game data in this function
void finalize()
{
  delete scene;
  delete input_handler;
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

void CheckInput() {
  if (is_key_pressed(VK_ESCAPE))
    schedule_quit_game();

  input_handler->CheckSpace(is_key_pressed(VK_SPACE));

  input_handler->CheckLeftArrow(is_key_pressed(VK_LEFT));
  input_handler->CheckRightArrow(is_key_pressed(VK_RIGHT));
  input_handler->CheckUpArrow(is_key_pressed(VK_UP));
  input_handler->CheckDownArrow(is_key_pressed(VK_DOWN));

  input_handler->CheckLeftMouse(is_mouse_button_pressed(0));
  input_handler->CheckRightMouse(is_mouse_button_pressed(1));

  input_handler->CheckMousePos(Vector2{get_cursor_x(), get_cursor_y()});
}

void RegisterCallback() {
  dispatcher.GetSink<LeftArrowDown>().Connect<&PlayerEventHandler::RespondLeftArrowDown>(*player_event_handler);
  dispatcher.GetSink<LeftArrowUp>().Connect<&PlayerEventHandler::RespondLeftArrowUp>(*player_event_handler);

  dispatcher.GetSink<RightArrowDown>().Connect<&PlayerEventHandler::RespondRightArrowDown>(*player_event_handler);
  dispatcher.GetSink<RightArrowUp>().Connect<&PlayerEventHandler::RespondRightArrowUp>(*player_event_handler);

  dispatcher.GetSink<UpArrowDown>().Connect<&PlayerEventHandler::RespondUpArrowDown>(*player_event_handler);
  dispatcher.GetSink<UpArrowUp>().Connect<&PlayerEventHandler::RespondUpArrowUp>(*player_event_handler);

  dispatcher.GetSink<DownArrowDown>().Connect<&PlayerEventHandler::RespondDownArrowDown>(*player_event_handler);
  dispatcher.GetSink<DownArrowUp>().Connect<&PlayerEventHandler::RespondDownArrowUp>(*player_event_handler);

  dispatcher.GetSink<LeftMouseDown>().Connect<&PlayerEventHandler::RespondLMBDown>(*player_event_handler);
  dispatcher.GetSink<LeftMouseUp>().Connect<&PlayerEventHandler::RespondLMBUp>(*player_event_handler);
}