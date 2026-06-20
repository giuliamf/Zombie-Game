#include "WaveSpawner.h"
#include "State.h"
#include "GameObject.h"
#include "Zombie.h"
#include "SpriteRenderer.h"
#include "Animator.h"
#include "Animation.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

WaveSpawner::WaveSpawner(GameObject& associated, State* state)
    : Component(associated),
      state(state),
      currentWave(0),
      spawnedZombies(0)
{
}

void WaveSpawner::Start() {
    // Inicializar waves com dificuldade crescente
    waves.push_back(Wave(5, 1.0f));    // Wave 1: 5 zombies, 1.0s de intervalo
    waves.push_back(Wave(10, 0.7f));   // Wave 2: 10 zombies, 0.7s de intervalo
    waves.push_back(Wave(15, 0.5f));   // Wave 3: 15 zombies, 0.5s de intervalo
    waves.push_back(Wave(20, 0.4f));   // Wave 4: 20 zombies, 0.4s de intervalo (extra)
    waves.push_back(Wave(30, 0.3f));   // Wave 5: 30 zombies, 0.3s de intervalo (extra)
    
    std::cout << "[WaveSpawner] Iniciado! Total de waves: " << waves.size() << std::endl;
    std::cout << "[WaveSpawner] Wave 1 começou! Zombies: " << waves[0].zombieCount << std::endl;
    
    // Inicializar timer
    spawnTimer.Restart();
}

void WaveSpawner::Update(float dt) {
    // Verificar se ainda há waves para processar
    if (currentWave >= waves.size()) {
        return; // Silenciosamente retornar se todas as waves foram completadas
    }
    
    // Debug: verificar se Update está sendo chamado
    static float debugTimer = 0;
    debugTimer += dt;
    if (debugTimer >= 5.0f) {
        std::cout << "[WaveSpawner DEBUG] Update rodando. Wave: " << (currentWave + 1)
                  << ", Spawnados: " << spawnedZombies << "/" << waves[currentWave].zombieCount
                  << ", Timer: " << spawnTimer.Get() << "s" << std::endl;
        debugTimer = 0;
    }
    
    // Atualizar timer
    spawnTimer.Update(dt);
    
    Wave& currentWaveData = waves[currentWave];
    
    // Verificar se ainda há zombies para spawnar nesta wave
    if (spawnedZombies < currentWaveData.zombieCount) {
        // Verificar se é hora de spawnar um novo zombie
        if (spawnTimer.Get() >= currentWaveData.spawnInterval) {
            SpawnZombie();
            spawnedZombies++;
            spawnTimer.Restart();
            
            std::cout << "[WaveSpawner] Zombie spawnado! (" 
                      << spawnedZombies << "/" << currentWaveData.zombieCount 
                      << ") Wave " << (currentWave + 1) << std::endl;
        }
    } else {
        // Wave atual completa, avançar para próxima
        NextWave();
    }
}

void WaveSpawner::SpawnZombie() {
    // ÁREA PEQUENA PARA TESTE - ao redor do player inicial
    // Player inicial: X=1280, Y=1300
    
    const float PLAYER_X = 1280.0f;
    const float PLAYER_Y = 1300.0f;
    const float SPAWN_DISTANCE = 300.0f; // Distância do player para spawnar
    const float SPAWN_RANGE = 200.0f;    // Variação na posição
    
    float x, y;
    
    // Escolher lado aleatório para spawn (0=cima, 1=direita, 2=baixo, 3=esquerda)
    int side = rand() % 4;
    
    switch(side) {
        case 0: // Cima
            x = PLAYER_X - SPAWN_RANGE/2 + static_cast<float>(rand() % static_cast<int>(SPAWN_RANGE));
            y = PLAYER_Y - SPAWN_DISTANCE;
            break;
        case 1: // Direita
            x = PLAYER_X + SPAWN_DISTANCE;
            y = PLAYER_Y - SPAWN_RANGE/2 + static_cast<float>(rand() % static_cast<int>(SPAWN_RANGE));
            break;
        case 2: // Baixo
            x = PLAYER_X - SPAWN_RANGE/2 + static_cast<float>(rand() % static_cast<int>(SPAWN_RANGE));
            y = PLAYER_Y + SPAWN_DISTANCE;
            break;
        case 3: // Esquerda
            x = PLAYER_X - SPAWN_DISTANCE;
            y = PLAYER_Y - SPAWN_RANGE/2 + static_cast<float>(rand() % static_cast<int>(SPAWN_RANGE));
            break;
        default:
            x = PLAYER_X;
            y = PLAYER_Y + 200.0f;
            break;
    }
    
    // Debug: mostrar posição de spawn
    std::cout << "[WaveSpawner] Spawnando zombie em X=" << x << " Y=" << y << std::endl;
    
    // Criar GameObject do zombie (exatamente como State::CreateZombie)
    GameObject* zombie = new GameObject();
    
    zombie->box.pos.x = x;
    zombie->box.pos.y = y;
    zombie->box.size.x = 72;
    zombie->box.size.y = 72;
    
    // Adicionar SpriteRenderer
    SpriteRenderer* sr = new SpriteRenderer(
        *zombie,
        "Resources/img/Enemy.png",
        3, 2
    );
    zombie->AddComponent(sr);
    
    // Adicionar Animator
    Animator* animator = new Animator(*zombie);
    animator->AddAnimation("walk", Animation(0, 2, 0.2f));
    zombie->AddComponent(animator);
    
    // Adicionar componente Zombie
    zombie->AddComponent(new Zombie(*zombie));
    
    // Setar animação ANTES de adicionar ao State
    // (AddObject chama Start() imediatamente se o jogo já começou)
    animator->SetAnimation("walk");
    
    // Agora adicionar ao State
    state->AddObject(zombie);
}

void WaveSpawner::NextWave() {
    currentWave++;
    spawnedZombies = 0;
    spawnTimer.Restart();
    
    if (currentWave < waves.size()) {
        std::cout << "\n========================================" << std::endl;
        std::cout << "[WaveSpawner] Wave " << (currentWave + 1) << " começou!" << std::endl;
        std::cout << "[WaveSpawner] Zombies: " << waves[currentWave].zombieCount << std::endl;
        std::cout << "[WaveSpawner] Intervalo: " << waves[currentWave].spawnInterval << "s" << std::endl;
        std::cout << "========================================\n" << std::endl;
    } else {
        std::cout << "\n========================================" << std::endl;
        std::cout << "[WaveSpawner] TODAS AS WAVES COMPLETADAS!" << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
}

bool WaveSpawner::Is(std::string type) const {
    return type == "WaveSpawner";
}

int WaveSpawner::GetCurrentWave() const {
    return currentWave;
}

int WaveSpawner::GetSpawnedZombies() const {
    return spawnedZombies;
}

int WaveSpawner::GetTotalZombiesInWave() const {
    if (currentWave < waves.size()) {
        return waves[currentWave].zombieCount;
    }
    return 0;
}

bool WaveSpawner::IsWaveComplete() const {
    return currentWave >= waves.size();
}

// Made with Bob
