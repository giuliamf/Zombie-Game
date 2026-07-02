#pragma once

#include "State.h"
#include "Text.h"

class TitleState : public State {
public:
    TitleState();
    ~TitleState() override;

    void LoadAssets() override;
    void Update(float dt) override;
    void Render() override;
    void Start() override;
    void Pause() override;
    void Resume() override;

private:
    Text*  blinkText;    // ponteiro para o componente de texto piscante
    float  blinkTimer;   // acumulador de tempo para o efeito
    bool   textVisible;  // estado atual da visibilidade
};
