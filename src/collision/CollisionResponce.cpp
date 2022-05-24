#include "CollisionResponce.hpp"
#include "Components.hpp"
#include <cassert>
#include <algorithm>
#include <Engine.h>
#include <iostream>

void CollisionResponcer::ResponceCollision(EntityHandle& e1, EntityHandle& e2) {
    assert(e1.HasComponent<EntityTypeComponent>());
    assert(e2.HasComponent<EntityTypeComponent>());
    int type1 = e1.GetComponent<EntityTypeComponent>()->type;
    int type2 = e2.GetComponent<EntityTypeComponent>()->type;
    if (type1 > type2) {
        std::swap(type1, type2);
        std::swap(e1, e2);
    }
    if (responce_collision_virtual_table_[type1][type2] != nullptr) {
        (*responce_collision_virtual_table_[type1][type2])(e1, e2);
    }
}

void ResponceCollisionPW(EntityHandle& e1, EntityHandle& e2) {
    // pass
}

void ResponceCollisionPE(EntityHandle& e1, EntityHandle& e2) {
    // lose
    schedule_quit_game();
}

void ResponceCollisionPB(EntityHandle& e1, EntityHandle& e2) {
    assert(e1.HasComponent<Health>());
    assert(e2.HasComponent<Damage>());
    e1.GetComponent<Health>()->current_value -= e2.GetComponent<Damage>()->damage;
    if (!e2.HasComponent<OnDelete>()) {
        e2.AddComponent<OnDelete>();
    }
    if (e1.GetComponent<Health>()->current_value <= 0 && !e1.HasComponent<OnDelete>()) {
        e1.AddComponent<OnDelete>();
    }
}

void ResponceCollisionWE(EntityHandle& e1, EntityHandle& e2) {
    assert(e2.HasComponent<Speed>());
    assert(e2.HasComponent<CollisionShape>());
    CollisionCircle* phys_circle = dynamic_cast<CollisionCircle*>(e2.GetComponent<CollisionShape>()->form);
    CollisionWall* phys_wall = dynamic_cast<CollisionWall*>(e1.GetComponent<CollisionShape>()->form);
    assert(phys_circle != nullptr);
    assert(phys_wall != nullptr);
    Vector2 v1 = phys_wall->GetFirstPoint();
    Vector2 v2 = phys_wall->GetSecondPoint();
    Vector2 v3 = v2 - v1;
    Vector2 a = phys_circle->GetCenter() - v1;
    Vector2 b = a.GetProjection(v3);

    Vector2 speed = e2.GetComponent<Speed>()->speed;

    Vector2 projection = (speed).GetProjection(v3);

    Vector2 dir = projection - speed;
    if (dir * (a - b) < 0) {
        dir = -dir;
    }

    Vector2 speed_reflection = dir + projection;
    e2.GetComponent<Speed>()->speed = speed_reflection;
}

void ResponceCollisionWB(EntityHandle& e1, EntityHandle& e2) {
    e2.AddComponent<OnDelete>();
}

void ResponceCollisionEB(EntityHandle& e1, EntityHandle& e2) {
    assert(e1.HasComponent<Health>());
    assert(e2.HasComponent<Damage>());
    e1.GetComponent<Health>()->current_value -= e2.GetComponent<Damage>()->damage;
    if (!e2.HasComponent<OnDelete>()) {
        e2.AddComponent<OnDelete>();
    }
    if (e1.GetComponent<Health>()->current_value <= 0 && !e1.HasComponent<OnDelete>()) {
        e1.AddComponent<OnDelete>();
    }
}