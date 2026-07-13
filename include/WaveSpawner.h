#pragma once

#include "Component.h"
#include "Timer.h"
#include <vector>

// Estrutura que define uma wave
struct Wave {
    int zombieCount;      // Quantidade de zombies nesta wave
    float spawnInterval;  // Intervalo entre spawns (em segundos)
    
    Wave(int count, float interval) 
        : zombieCount(count), spawnInterval(interval) {}
};

class State;

class WaveSpawner : public Component {
public:
    WaveSpawner(GameObject& associated, State* state);
    
    void Start() override;
    void Update(float dt) override;
    bool Is(std::string type) const override;
    
    // Getters para informações da wave atual
    int GetCurrentWave() const;
    int GetSpawnedZombies() const;
    int GetTotalZombiesInWave() const;
    bool IsWaveComplete() const;
    
private:
    State* state;                    // Referência ao State para criar zombies
    std::vector<Wave> waves;         // Lista de waves
    int currentWave;                 // Índice da wave atual
    int spawnedZombies;              // Quantos zombies já foram spawnados na wave atual
    Timer spawnTimer;                // Timer para controlar intervalo de spawn
    
    void SpawnZombie();              // Cria um zombie em posição aleatória
    void NextWave();                 // Avança para próxima wave
};

// Made with Bob
