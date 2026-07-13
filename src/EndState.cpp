#include "EndState.h"
#include "Camera.h"
#include "Game.h"
#include "GameData.h"
#include "GameObject.h"
#include "InputManager.h"
#include "SpriteRenderer.h"
#include "TitleState.h"
#include "Text.h"

#include <SDL2/SDL.h>

static const char* END_FONT_PATH      = "Resources/font/font.ttf";
static const int   END_FONT_SIZE      = 28;
static const float END_BLINK_INTERVAL = 0.5f;
static const char* END_BLINK_MSG      = "SPACE: jogar novamente   ESC: sair";

EndState::EndState()
    : blinkText(nullptr),
      blinkTimer(0.0f),
      textVisible(true)
{
    LoadAssets();

    // BACKGROUND — depende do resultado da partida
    const char* bgPath = GameData::playerVictory
        ? "Resources/img/Win.png"
        : "Resources/img/Lose.png";

    GameObject* bg = new GameObject();
    bg->box.pos.x = 0;
    bg->box.pos.y = 0;
    bg->AddComponent(new SpriteRenderer(*bg, bgPath));
    AddObject(bg);

    // TEXTO PISCANTE com instrução de input
    SDL_Color white = {255, 255, 255, 255};

    GameObject* textGo = new GameObject();
    blinkText = new Text(*textGo, END_FONT_PATH, END_FONT_SIZE,
                         BLENDED, END_BLINK_MSG, white);
    textGo->AddComponent(blinkText);

    textGo->box.pos.x = 600 - blinkText->GetWidth() / 2.0f;
    textGo->box.pos.y = 820;

    AddObject(textGo);
}

EndState::~EndState() {
}

void EndState::LoadAssets() {
    const char* musicPath = GameData::playerVictory
        ? "Resources/audio/endStateWin.ogg"
        : "Resources/audio/endStateLose.ogg";
    music.Open(musicPath);
    music.Play();
}

void EndState::Start() {
    StartArray();
    // resetar câmera: EndState renderiza em coordenadas de tela (0,0)
    Camera::pos.x = 0;
    Camera::pos.y = 0;
}

void EndState::Pause() {
}

void EndState::Resume() {
}

void EndState::Update(float dt) {
    if (SDL_QuitRequested()) {
        quitRequested = true;
        return;
    }

    InputManager& input = InputManager::GetInstance();

    if (input.IsKeyDown(SDLK_ESCAPE)) {
        quitRequested = true;
        return;
    }

    if (input.IsKeyDown(SDLK_SPACE)) {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
        return;
    }

    if (blinkText != nullptr) {
        blinkTimer += dt;
        if (blinkTimer >= END_BLINK_INTERVAL) {
            blinkTimer -= END_BLINK_INTERVAL;
            textVisible = !textVisible;
            blinkText->SetText(textVisible ? END_BLINK_MSG : "");
        }
    }

    UpdateArray(dt);
}

void EndState::Render() {
    RenderArray();
}
