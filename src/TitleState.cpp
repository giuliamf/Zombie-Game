#include "TitleState.h"
#include "Game.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "StageState.h"
#include "Text.h"

#include <SDL2/SDL.h>

static const char* FONT_PATH  = "Resources/font/font.ttf";
static const int   FONT_SIZE  = 28;
static const float BLINK_INTERVAL = 0.5f;
static const char* BLINK_MSG  = "Pressione ESPACO para iniciar";

TitleState::TitleState()
    : blinkText(nullptr),
      blinkTimer(0.0f),
      textVisible(true)
{
    LoadAssets();

    // BACKGROUND
    GameObject* bg = new GameObject();
    bg->box.pos.x = 0;
    bg->box.pos.y = 0;
    bg->AddComponent(
        new SpriteRenderer(
            *bg,
            "Resources/img/Title.png"
        )
    );
    AddObject(bg);

    // TEXTO PISCANTE
    SDL_Color white = {255, 255, 255, 255};

    GameObject* textGo = new GameObject();
    blinkText = new Text(*textGo, FONT_PATH, FONT_SIZE, BLENDED, BLINK_MSG, white);
    textGo->AddComponent(blinkText);

    // posicionar no centro inferior da janela (600, 750 para 1200x900)
    textGo->box.pos.x = 600 - blinkText->GetWidth() / 2.0f;
    textGo->box.pos.y = 750;

    AddObject(textGo);
}

TitleState::~TitleState() {
}

void TitleState::LoadAssets() {
}

void TitleState::Start() {
    StartArray();
}

void TitleState::Pause() {
}

void TitleState::Resume() {
}

void TitleState::Update(float dt) {
    // Fechar janela pelo botão X
    if (SDL_QuitRequested()) {
        quitRequested = true;
        return;
    }

    InputManager& input = InputManager::GetInstance();

    // ESC — encerra o jogo
    if (input.IsKeyDown(SDLK_ESCAPE)) {
        quitRequested = true;
        return;
    }

    // SPACE — inicia o jogo
    if (input.IsKeyDown(SDLK_SPACE)) {
        Game::GetInstance().Push(new StageState());
    }

    // efeito piscante: alterna visibilidade a cada BLINK_INTERVAL segundos
    if (blinkText != nullptr) {
        blinkTimer += dt;
        if (blinkTimer >= BLINK_INTERVAL) {
            blinkTimer -= BLINK_INTERVAL;
            textVisible = !textVisible;
            blinkText->SetText(textVisible ? BLINK_MSG : "");
        }
    }

    UpdateArray(dt);
}

void TitleState::Render() {
    RenderArray();
}
