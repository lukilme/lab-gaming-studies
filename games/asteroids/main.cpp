#include "./models/configs.hpp"
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


typedef struct Player{
    Rectangle body;
    Vector2 speed;
    Color color;
} Player;

typedef struct Enemy{
    Rectangle body;
    Vector2 speed;
    bool active;
    Color color;
} Enemy;

typedef struct Shoot{
    Rectangle body;
    Vector2 speed;
    bool active;
    Color color;
} Shoot;

typedef enum { FIRST = 0, SECOND, THIRD } EnemyWave;

GameConfig config;
static Player player = { 0 };
static Enemy enemies[NUM_MAX_ENEMIES] = { 0 };
static Shoot shoots[NUM_SHOOTS] = { 0 };
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
}

void InitGame(void) {
  config.shootRate = 0;
  config.pause = false;
  config.gameOver = false;
  config.victory = false;
  config.smooth = false;
  wave = FIRST;
  config.activeEnemies = FIRST_WAVE;
  config.enemiesKill = 0;
  config.score = 0;
  config.alpha = 0.0f;

  player.body = { 5, 5, 20, 20 }; 
  player.speed = { 5, 5 };
  player.color = { 20, 50, 20, 255 };

  for (int i = 0; i < NUM_MAX_ENEMIES; i++) {
    enemies[i].body.width = 10;
    enemies[i].body.height = 10;
    enemies[i].body.x = GetRandomValue(screenWidth, screenWidth + 1000);
    enemies[i].body.y = GetRandomValue(0, screenHeight - enemies[i].body.height);
    enemies[i].speed.x = 5;
    enemies[i].speed.y = 5;
    enemies[i].active = true;
    enemies[i].color = GRAY;  
  }

  for (int i = 0; i < NUM_SHOOTS; i++) {
    shoots[i].active = false;
    shoots[i].body = { 200, 0, 10, 10 };  
    shoots[i].speed = { 3, 3 };
    shoots[i].color = { 0, 0, 255, 255 };
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

      for(int i = 0; i < config.activeEnemies; i++){
        if(CheckCollisionRecs(player.body, enemies[i].body)) config.gameOver = true;
      }

      for(int i = 0; i < config.activeEnemies; i++){
        if(enemies[i].active){
          enemies[i].body.x -= enemies[i].speed.x;

          if(enemies[i].body.x < 0){
            enemies[i].body.x = GetRandomValue(screenWidth, screenHeight + 1000);
            enemies[i].body.y = GetRandomValue(0, screenHeight - enemies[i].body.height);
          }
        }
      }

      if(player.body.x <= 0) player.body.x = 0;
      if(player.body.x + player.body.width >= screenWidth) player.body.x = screenWidth - player.body.width;
      if(player.body.y <= 0) player.body.y = 0;
      if(player.body.y + player.body.height >= screenHeight) player.body.y = screenHeight - player.body.height;

      if(IsKeyDown(KEY_SPACE)){
        config.shootRate += 5;

        for(int i = 0; i < NUM_SHOOTS; i++){
          if(!shoots[i].active && config.shootRate%20 == 0){
            shoots[i].body.x = player.body.x;
            shoots[i].body.y = player.body.y + player.body.height/4;
            shoots[i].active = true;
            break;
          }
        }
      }


      for(int i = 0; i < NUM_SHOOTS; i++){

        if(shoots[i].active){

          shoots[i].body.x += shoots[i].speed.x;

          for(int j = 0; j < config.activeEnemies; j++){

            if(enemies[j].active){
              if(CheckCollisionRecs(shoots[i].body, enemies[j].body)){
                shoots[i].active = false;
                enemies[j].body.x = GetRandomValue(screenWidth, screenWidth + 1000);
                enemies[j].body.y = GetRandomValue(0, screenHeight - enemies[j].body.height);
                config.shootRate = 0;
                config.enemiesKill++;
                config.score+=100;
              }
              if (shoots[i].body.x + shoots[i].body.width >= screenWidth){
                shoots[i].active = false;
                config.shootRate = 0;
              }
            }
          }
        }
      }
    }
  }
  else{
    if(IsKeyPressed(KEY_ENTER)){
      InitGame();
      config.gameOver = false;
    }
  }
}

void DrawGame(void) {
  BeginDrawing();
  ClearBackground({20, 20, 20});

  if (!config.gameOver) {
    DrawRectangleRec(player.body, player.color);

    if (wave == FIRST) DrawText("FIRST WAVE", screenWidth/2 - MeasureText("FIRST WAVE", 40)/2, screenHeight/2 - 40, 40, Fade(BLACK, config.alpha));
    else if (wave == SECOND) DrawText("SECOND WAVE", screenWidth/2 - MeasureText("SECOND WAVE", 40)/2, screenHeight/2 - 40, 40, Fade(BLACK, config.alpha));
    else if (wave == THIRD) DrawText("THIRD WAVE", screenWidth/2 - MeasureText("THIRD WAVE", 40)/2, screenHeight/2 - 40, 40, Fade(BLACK, config.alpha));


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