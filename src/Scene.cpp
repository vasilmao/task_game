#include "Scene.hpp"
#include "ecs/Api.hpp"

Scene::Scene(EntityRegistry& registry) : registry_{registry} {
}

void Scene::AddEntity(const EntityHandle& handle) {
    entities_.push_back(handle);
}

std::list<EntityHandle>& Scene::GetEntities() {
    return entities_;
}

Scene::~Scene() {
    for (auto it = entities_.begin(); it != entities_.end(); ++it) {
        it->Destroy();
    }
}