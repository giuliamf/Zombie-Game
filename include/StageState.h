#pragma once

#include "State.h"
#include "Music.h"
#include "TileSet.h"

#include <memory>

class StageState : public State {
public:
    StageState();
    ~StageState() override;

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;
    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Music music;
    std::unique_ptr<TileSet> mapTileSet;
    bool endTriggered; // impede que a transição para EndState dispare mais de uma vez

    GameObject* CreateZombie(float x, float y);
};
