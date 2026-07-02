#pragma once

#include <vector>
#include <memory>
#include "GameObject.h"

class State {
public:
    State();
    virtual ~State();

    // Pure virtual lifecycle interface
    virtual void LoadAssets() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Start() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;

    // Concrete object-management helpers
    virtual std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);
    std::vector<std::shared_ptr<GameObject>>& GetObjectArray();

    // Array lifecycle helpers — call these from subclass Start/Update/Render
    void StartArray();
    void UpdateArray(float dt);
    void RenderArray();

    bool QuitRequested() const;
    bool PopRequested() const;

protected:
    bool popRequested;
    bool quitRequested;
    bool started;

    std::vector<std::shared_ptr<GameObject>> objectArray;
    std::vector<std::shared_ptr<GameObject>> pendingObjects;
};
