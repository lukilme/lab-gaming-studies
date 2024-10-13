#include "configs.hpp"

GameConfig::GameConfig() 
    : gameOver(false), pause(false), score(0), victory(false), 
      shootRate(0), alpha(0.0f), activeEnemies(0), enemiesKill(0), smooth(false) {

}