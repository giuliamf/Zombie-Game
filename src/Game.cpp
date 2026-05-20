#include "Game.h"
#include "InputManager.h"

#include <iostream>

// variável estática 
Game* Game::instance = nullptr;

// verifica se já existe um jogo, se não existir, cria um novo e retorna uma ref para ele
Game& Game::GetInstance() {
    if (instance == nullptr) {
        instance = new Game(
            "Giulia Moura - 200018795",
            1200,
            900
        );
    }
    return *instance;
}

// para evitar lixo de memoria
Game::Game(const std::string& title, int width, int height)
    : window(nullptr), renderer(nullptr), state(nullptr)
{
    if (instance != nullptr) {
        std::cerr << "Erro: Game já foi instanciado!" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    instance = this;

    // inicia video, audio e temporizador
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
        std::cerr << "Erro SDL_Init: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // usar png e jpg
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if ((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
        std::cerr << "Erro IMG_Init: " << IMG_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // audio: ativa musicas mp3 e ogg
    if (Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) == 0) {
        std::cerr << "Erro Mix_Init: " << Mix_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // audio: inicializa o audio
    if (Mix_OpenAudio(
        MIX_DEFAULT_FREQUENCY,
        MIX_DEFAULT_FORMAT,
        MIX_DEFAULT_CHANNELS,
        1024
    ) != 0) {
        std::cerr << "Erro Mix_OpenAudio: " << Mix_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // reserva os canais de som 
    Mix_AllocateChannels(32);

    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    if (window == nullptr) {
        std::cerr << "Erro SDL_CreateWindow: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    // pega o melhor driver e usa a gpu
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED
    );

    if (renderer == nullptr) {
        std::cerr << "Erro SDL_CreateRenderer: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    state = new State();
}

// evitar vazamento de memoria
Game::~Game() {
    Mix_CloseAudio();
    Mix_Quit();

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

State& Game::GetState() {
    return *state;
}

// 30 fps
void Game::Run() {
    Uint32 startTime = 0;
    float dt = 0.0f;
    
    state->Start();
    while (!InputManager::GetInstance().QuitRequested()) {
        startTime = SDL_GetTicks();

        SDL_RenderClear(renderer);

        InputManager::GetInstance().Update();

        state->Update(dt);
        state->Render();
        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - startTime;
        dt = frameTime / 1000.0f;

        SDL_Delay(16);
    }
}
