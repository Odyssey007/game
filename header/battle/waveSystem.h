#pragma once
#include "../header/utility.h"
#include "../header/battle/pool.h"

class WaveSystem {
private:
    //timer
    sf::Clock spawnClock;
    //wave
    sf::Time minWaveDuration;
    sf::Time waveDuration;
    unsigned int waveNumber;
    //enemy
    size_t enemyLevel;
    size_t numEnemies;
    unsigned int maxEnemies;

    void updateWaveStat();
    void updateEnemyStat();
    void nextWave(size_t& numEnemies, size_t& enemyLvl);
public:
    WaveSystem();
    bool isUpdated(bool allDead, size_t& numEnemies, size_t& enemyLvl);
};