#include "Component.h"
#include "GameObject.h"
#include <iostream>


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
    
    std::cout << "[GameObject::Start] Iniciando GameObject com " << components.size() << " componentes" << std::endl;
    started = true;
    
    // Inicializar componentes em múltiplas passadas até que não haja mais novos componentes
    size_t lastProcessedIndex = 0;
    
    while (lastProcessedIndex < components.size()) {
        size_t currentSize = components.size();
        
        // Inicializar componentes que ainda não foram inicializados
        for (size_t i = lastProcessedIndex; i < currentSize; i++) {
            if (i >= components.size()) {
                std::cout << "[GameObject::Start] ERRO: índice " << i << " >= size " << components.size() << std::endl;
                break;
            }
            
            if (components[i] == nullptr) {
                std::cout << "[GameObject::Start] AVISO: componente nullptr no índice " << i << std::endl;
                continue;
            }
            
            std::cout << "[GameObject::Start] Chamando Start() no componente " << i << std::endl;
            components[i]->Start();
            std::cout << "[GameObject::Start] Start() do componente " << i << " completado" << std::endl;
        }
        
        lastProcessedIndex = currentSize;
    }
    
    std::cout << "[GameObject::Start] GameObject iniciado com sucesso. Total componentes: " << components.size() << std::endl;
}

void GameObject::Update(float dt) {
    Start();

    for (size_t i = 0; i < components.size(); i++) {
        if (i >= components.size()) {
            std::cout << "[GameObject::Update] ERRO: índice " << i << " >= size " << components.size() << std::endl;
            break;
        }
        
        if (components[i] == nullptr) {
            std::cout << "[GameObject::Update] AVISO: componente nullptr no índice " << i << std::endl;
            continue;
        }
        
        components[i]->Update(dt);
    }
}

void GameObject::Render() {
    for (size_t i = 0; i < components.size(); i++) {
        if (i >= components.size()) {
            std::cout << "[GameObject::Render] ERRO: índice " << i << " >= size " << components.size() << std::endl;
            break;
        }
        
        if (components[i] == nullptr) {
            std::cout << "[GameObject::Render] AVISO: componente nullptr no índice " << i << std::endl;
            continue;
        }
        
        components[i]->Render();
    }
}

void GameObject::AddComponent(Component* component) {
    if (component != nullptr) {
        components.emplace_back(component);
    }
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
        if (comp != nullptr) {
            comp->NotifyCollision(other);
        }
    }
}

Component* GameObject::GetComponent(std::string type) {

    for (auto& comp : components) {
        if (comp != nullptr && comp->Is(type)) {
            return comp;
        }
    }

    return nullptr;
}