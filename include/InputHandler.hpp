#pragma once

#include "Vector.hpp"
#include "event_system/EventSystem.hpp"

class InputHandler {
  public:
    InputHandler(Dispatcher& dispatcher) : dispatcher_{dispatcher},
        left_arrow_pressed_{false},
        right_arrow_pressed_{false},
        up_arrow_pressed_{false},
        down_arrow_pressed_{false},
        left_mouse_pressed_{false},
        right_mouse_pressed_{false} {}
    void CheckLeftArrow(bool is_down);
    void CheckRightArrow(bool is_down);
    void CheckUpArrow(bool is_down);
    void CheckDownArrow(bool is_down);
    void CheckSpace(bool is_down);
    void CheckLeftMouse(bool is_down);
    void CheckRightMouse(bool is_down);
    void CheckMousePos(const Vector2& pos);

  private:

    Dispatcher& dispatcher_;

    bool left_arrow_pressed_ : 1;
    bool right_arrow_pressed_ : 1;
    bool up_arrow_pressed_ : 1;
    bool down_arrow_pressed_ : 1;
    bool space_pressed_ : 1;

    bool left_mouse_pressed_ : 1;
    bool right_mouse_pressed_ : 1;

    Vector2 mouse_pos_;
};