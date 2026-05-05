#include "GameObject.h"
#include "Component.h"

GameObject::GameObject()
    : box(), started(false)
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

    for (Component* component : components) {
        component->Start();
    }

    started = true;
}

void GameObject::Update(float dt) {
    Start();

    for (Component* component : components) {
        component->Update(dt);
    }
}

void GameObject::Render() {
    for (Component* component : components) {
        component->Render();
    }
}

void GameObject::AddComponent(Component* component) {
    components.emplace_back(component);
}

std::vector<Component*>& GameObject::GetComponents() {
    return components;
}