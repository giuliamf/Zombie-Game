#pragma once

#include <vector>
#include <memory>
#include "Music.h"
#include "GameObject.h"
#include "TileSet.h"

class State {
public:
    State();
    ~State();

    void LoadAssets();
    void Start();
    void Update(float dt);
    void Render();

    bool QuitRequested();

    std::weak_ptr<GameObject> AddObject(GameObject* go);
    std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

    std::vector<std::shared_ptr<GameObject>>& GetObjectArray();


private:
    std::vector<std::shared_ptr<GameObject>> objectArray;
    Music music;
    bool quitRequested;

    std::unique_ptr<TileSet> mapTileSet;

    bool started;
};
