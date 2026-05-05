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

    void AddObject(GameObject* go);

private:
    std::vector<std::unique_ptr<GameObject>> objectArray;
    Music music;
    bool quitRequested;

    std::unique_ptr<TileSet> mapTileSet;
};
