#pragma once

#include "State.h"
#include "Music.h"
#include "Text.h"

class EndState : public State {
public:
    EndState();
    ~EndState() override;

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;
    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Music music;

    Text* blinkText;
    float blinkTimer;
    bool  textVisible;
};
