#pragma once

#include "Rect.h"

#include <vector>
#include <string>

class Component;

class GameObject {
public:
    Component* GetComponent(std::string type);
    GameObject();
    ~GameObject();

    void Start(); // garante que o start() roda só uma vez
    void Update(float dt);
    void Render();

    void AddComponent(Component* component); // composição 

    std::vector<Component*>& GetComponents();

    Rect box;

    double angleDeg;

    void RequestDelete();
    bool IsDead() const;

    void NotifyCollision(GameObject& other);


private:
    std::vector<Component*> components; // lista dinâmica de componentes
    bool started;
    bool isDead;
};