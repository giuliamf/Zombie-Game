#pragma once

class GameObject;

class Component {
public:
    explicit Component(GameObject& associated);
    virtual ~Component();

    virtual void Start();
    virtual void Update(float dt);
    virtual void Render();

protected:
    GameObject& associated;
};
