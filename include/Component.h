#pragma once
#include <string>

class GameObject;

class Component {
public:
    explicit Component(GameObject& associated);
    virtual ~Component();

    virtual void Start() {};
    virtual void Update(float dt);
    virtual void Render();
    virtual void NotifyCollision(GameObject& other) {}
    virtual bool Is(std::string type) const {
        return false;
    }

protected:
    GameObject& associated;
};
