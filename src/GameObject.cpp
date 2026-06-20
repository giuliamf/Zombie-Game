#include "Component.h"
#include "GameObject.h"


GameObject::GameObject()
    : box(), started(false), angleDeg(0), isDead(false)
{
}

GameObject::~GameObject() {
    for (Component* component : components) {
        delete component;
    }
}

void GameObject::Start() {
    if (started)
        return;
    
    started = true;
    
    // Usar índice ao invés de iterador, pois Start() pode adicionar componentes
    for (size_t i = 0; i < components.size(); i++) {
        if (components[i] != nullptr) {
            components[i]->Start();
        }
    }
}

void GameObject::Update(float dt) {
    Start();

    for (Component* component : components) {
        if (component != nullptr) {
            component->Update(dt);
        }
    }
}

void GameObject::Render() {
    for (Component* component : components) {
        if (component != nullptr) {
            component->Render();
        }
    }
}

void GameObject::AddComponent(Component* component) {
    components.emplace_back(component);
}

std::vector<Component*>& GameObject::GetComponents() {
    return components;
}

void GameObject::RequestDelete() {
    isDead = true;
}

bool GameObject::IsDead() const {
    return isDead;
}

void GameObject::NotifyCollision(GameObject& other) {
    for (auto& comp : components) {
        comp->NotifyCollision(other);
    }
}

Component* GameObject::GetComponent(std::string type) {

    for (auto& comp : components) {
        if (comp->Is(type)) {
            return comp;
        }
    }

    return nullptr;
}