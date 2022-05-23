#include "Vector.hpp"
#include "Renderer.hpp"
#include "EntityTypes.hpp"
#include "CollisionTypes.hpp"
#include <functional>

struct Health {
    int current_value;
    int max_value = 100;
};

struct RenderComponent {
    std::function<void(Renderer&)> render; // rotation
};

struct Transform {
    Vector2 pos; // center
    float rotation;
};

struct EntityTypeComponent {
    EntityTypeId type_;
};

struct CollisionShape {
    // everything is circle
    // Vector2 pos;
    ICollisionShape* form;
    ~CollisionShape() {
        delete form;
    }
};