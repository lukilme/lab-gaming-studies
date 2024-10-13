#include "./models/configs.hpp"
#include "./models/enemy.hpp"
#include "./models/player.hpp"
#include "./models/shoot.hpp"
#include "raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

static const int screenWidth = 800;
static const int screenHeight = 450;

#define NUM_SHOOTS 50
#define NUM_MAX_ENEMIES 50
#define FIRST_WAVE 10
#define SECOND_WAVE 20
#define THIRD_WAVE 50

typedef enum { FIRST = 0, SECOND, THIRD } EnemyWave;

GameConfig config;
Player player;
Enemy enemies[NUM_MAX_ENEMIES];
Shoot shoots[NUM_SHOOTS];
static EnemyWave wave;

static void InitGame(void);
static void UpdateGame(void);
static void DrawGame(void);
static void UnloadGame(void);
static void UpdateDrawFrame(void);

int main() {
    InitWindow(screenWidth, screenHeight, "Asteroids");
    InitGame();

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
    #else
        SetTargetFPS(60);
        while (!WindowShouldClose()){
            
            UpdateDrawFrame();
        }
    #endif
        UnloadGame();
        CloseWindow();
        return 0;

    return 0;
}

void InitGame(void) {
  wave = FIRST;
  player = Player("John Doe", {5, 5}, {20, 50, 20, 255});

  for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
    enemies[i] = Enemy(false, {50, 50}, {0, 255, 0, 255});
  }

  for (int i = 0; i < NUM_SHOOTS; i++) {
    shoots[i] = Shoot(false, {200, 0}, {0, 0, 255, 255});
  }
}

void UpdateGame(void) {
  if (!config.gameOver) {
    if (IsKeyPressed('P')) {
      config.pause = !config.pause;
    }

    if (!config.pause) {
      switch(wave) {
        case FIRST: {
          if (!config.smooth) {
            config.alpha += 0.02f;
            if (config.alpha >= 1.0f)
              config.smooth = true;
          }

          if (config.smooth) {
            config.alpha -= 0.02f;
          }

          if (config.enemiesKill == config.activeEnemies) {
            config.enemiesKill = 0;

            for (int i = 0; i < config.activeEnemies; i++) {
              if (!enemies[i].active)
                enemies[i].active = true;
            }

            config.activeEnemies = SECOND_WAVE;
            wave = SECOND;
            config.smooth = false;
            config.alpha = 0.0f;
          }
        } break;
        case SECOND: {
          if (!config.smooth) {
            config.alpha += 0.02f;
            if (config.alpha >= 1.0f) {
              config.smooth = true;
            }
          }

          if (config.smooth) {
            config.alpha -= 0.02f;
          }

          if (config.enemiesKill == config.activeEnemies) {
            config.enemiesKill = 0;

            for (int i = 0; i < config.activeEnemies; i++) {
              if (!enemies[i].active) {
                enemies[i].active = true;
              }
            }

            config.activeEnemies = THIRD_WAVE;
            wave = THIRD;
            config.smooth = false;
            config.alpha = 0.0f;
          }

        } break;
        case THIRD: {
          if (!config.smooth) {
            config.alpha += 0.02f;
            if (config.alpha >= 1.0f) {
              config.smooth = true;
            }
          }

          if (config.smooth) {
            config.alpha -= 0.02f;
          };

          if (config.enemiesKill == config.activeEnemies) {
            config.victory = true;
          }
        } break;
        default:
          break;
      }
        if (IsKeyDown(KEY_RIGHT)) player.body.x += player.speed.x;
        if (IsKeyDown(KEY_LEFT)) player.body.x -= player.speed.x;
        if (IsKeyDown(KEY_UP)) player.body.y -= player.speed.y;
        if (IsKeyDown(KEY_DOWN)) player.body.y += player.speed.y;


    }
  }
}

void DrawGame(void) {
  BeginDrawing();
  ClearBackground({20, 20, 20});

  if (!config.gameOver) {
    DrawRectangleRec(player.body, player.color);

    for (int i = 0; i < config.activeEnemies; i++) {
      if (enemies[i].active)
        DrawRectangleRec(enemies[i].body, enemies[i].color);
    }

    for (int i = 0; i < NUM_SHOOTS; i++) {
      if (shoots[i].active)
        DrawRectangleRec(shoots[i].body, shoots[i].color);
    }

    DrawText(TextFormat("%04i", config.score), 20, 20, 40, GRAY);

    if (config.victory)
      DrawText("YOU WIN", screenWidth / 2 - MeasureText("YOU WIN", 40) / 2,
               screenHeight / 2 - 40, 40, WHITE);

    if (config.pause)
      DrawText("GAME PAUSED", screenWidth / 2 - MeasureText("GAME PAUSED", 40) / 2,
               screenHeight / 2 - 40, 40, WHITE);
  } else {
    DrawText("PRESS [ENTER] TO PLAY AGAIN",
             GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2,
             GetScreenHeight() / 2 - 50, 20, WHITE);
  }
  EndDrawing();
}

void UnloadGame(void) {}

void UpdateDrawFrame(void) {
  UpdateGame();
  DrawGame();
}