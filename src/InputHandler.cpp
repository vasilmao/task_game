#include "InputHandler.hpp"

#include "event_system/Events.hpp"

#define CheckFlag(event, flag)            \
  if (flag != is_down) {                  \
    if (is_down) {                        \
      dispatcher_.Trigger<event##Down>(); \
    } else {                              \
      dispatcher_.Trigger<event##Up>();   \
    }                                     \
    flag = is_down;                       \
  }

void InputHandler::CheckLeftArrow(bool is_down) { CheckFlag(LeftArrow, left_arrow_pressed_) }

void InputHandler::CheckRightArrow(bool is_down) { CheckFlag(RightArrow, right_arrow_pressed_) }

void InputHandler::CheckUpArrow(bool is_down) { CheckFlag(UpArrow, up_arrow_pressed_) }

void InputHandler::CheckDownArrow(bool is_down) { CheckFlag(DownArrow, down_arrow_pressed_) }

void InputHandler::CheckSpace(bool is_down) { CheckFlag(Space, space_pressed_) }

void InputHandler::CheckLeftMouse(bool is_down) { CheckFlag(LeftMouse, left_mouse_pressed_) }

void InputHandler::CheckRightMouse(bool is_down) { CheckFlag(RightMouse, right_mouse_pressed_) }

void InputHandler::CheckMousePos(const Vector2& pos) {
  if (pos != mouse_pos_) {
    dispatcher_.Trigger<MouseMoved>(pos - mouse_pos_, pos);
    mouse_pos_ = pos;
  }
}