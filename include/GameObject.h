#pragma once

#include <vector>
#include "Rect.h"

class Component;

class GameObject {
public:
    GameObject();
    ~GameObject();

    void Start(); // garante que o start() roda só uma vez
    void Update(float dt);
    void Render();

    void AddComponent(Component* component); // composição 

    Rect box;

private:
    std::vector<Component*> components; // lista dinâmica de componentes
    bool started;
};