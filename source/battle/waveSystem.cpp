#include "../header/battle/waveSystem.h"

WaveSystem::WaveSystem() {
    waveDuration = sf::seconds(60);
    minWaveDuration = sf::seconds(10);
    waveNumber = 1;
    //enemy
    maxEnemies = 25; numEnemies = 3;
    enemyLevel = 0;
}

//need to give numEnemies && enemyLevel
bool WaveSystem::isUpdated(bool allDead, size_t& numEnemies, size_t& enemyLvl) {
    if (allDead || spawnClock.getElapsedTime() >= waveDuration) {
        nextWave(numEnemies, enemyLvl);
        spawnClock.restart();
        return true;
    }
    return false;
}

void WaveSystem::nextWave(size_t& numEnemies, size_t& enemyLvl) {
    updateWaveStat();
    updateEnemyStat();

    numEnemies = this->numEnemies;
    enemyLvl = this->enemyLevel;
}

void WaveSystem::updateWaveStat() {
    waveNumber++;
    waveDuration *= 0.95f;
    waveDuration = std::min(minWaveDuration, waveDuration);
}

void WaveSystem::updateEnemyStat() {
    //scales enemy lvl
    if (waveNumber <= 12 && waveNumber%3 == 0) {
        enemyLevel++;
    } else if (waveNumber > 12) {
        enemyLevel = enemyLevel*std::pow(waveNumber, 2);
    }
    //scales num of enemies
    if (waveNumber <= 12 && waveNumber%2 == 0) {
        numEnemies += 3;
    } else if (waveNumber > 12 && numEnemies <= maxEnemies) {
        numEnemies = numEnemies*std::log(waveNumber+1);
    }
    //locks numEnemies to maxEnemies
    if (numEnemies >= maxEnemies) {
        numEnemies = maxEnemies;
    }
}