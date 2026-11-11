# c언어와 raylib를 활용환 스네이크 게임 제작

```
#include "raylib.h"
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#define GRID_SIZE     20
#define MAX_SNAKE_LEN ((SCREEN_WIDTH / GRID_SIZE) * (SCREEN_HEIGHT / GRID_SIZE))

// 방향 구조체
typedef struct {
    int x;
    int y;
} Vector2i;

// 뱀 구조체
typedef struct {
    Vector2i body[MAX_SNAKE_LEN];
    int length;
    Vector2i dir;
} Snake;

// 먹이 구조체
typedef struct {
    Vector2i pos;
    bool active;
} Food;

// 게임 상태
typedef enum {
    TITLE,
    GAMEPLAY,
    GAMEOVER
} GameState;

// 먹이 위치 무작위 생성
static void RespawnFood(Food *food, const Snake *snake) {
    bool onSnake;
    int gridW = SCREEN_WIDTH / GRID_SIZE;
    int gridH = SCREEN_HEIGHT / GRID_SIZE;

    do {
        onSnake = false;
        food->pos.x = rand() % gridW;
        food->pos.y = rand() % gridH;

        for (int i = 0; i < snake->length; i++) {
            if (snake->body[i].x == food->pos.x && snake->body[i].y == food->pos.y) {
                onSnake = true;
                break;
            }
        }
    } while (onSnake);

    food->active = true;
}

// 게임 초기화
static void InitGame(Snake *snake, Food *food, GameState *state, int *score) {
    snake->length = 3;
    snake->dir.x = 1;
    snake->dir.y = 0;

    int startX = (SCREEN_WIDTH / GRID_SIZE) / 2;
    int startY = (SCREEN_HEIGHT / GRID_SIZE) / 2;

    for (int i = 0; i < snake->length; i++) {
        snake->body[i].x = startX - i;
        snake->body[i].y = startY;
    }

    *score = 0;
    *state = GAMEPLAY;
    RespawnFood(food, snake);
}

int main(void) {
    // 윈도우 창 및 난수 초기화
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "raylib C Snake Game");
    SetTargetFPS(60);
    srand((unsigned int)time(NULL));

    Snake snake;
    Food food;
    GameState state = TITLE;
    int score = 0;

    float moveTimer = 0.0f;
    const float moveInterval = 0.1f; // 0.1초마다 뱀 이동

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // -------------------------------------------------------------
        // 1. 입력 처리 및 상태 갱신 (Update)
        // -------------------------------------------------------------
        switch (state) {
            case TITLE:
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
                    InitGame(&snake, &food, &state, &score);
                }
                break;

            case GAMEPLAY:
                // 키 입력에 따른 방향 전환 (반대 방향 전환 불가 처리 포함)
                if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && snake.dir.y == 0) {
                    snake.dir.x = 0;
                    snake.dir.y = -1;
                } else if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && snake.dir.y == 0) {
                    snake.dir.x = 0;
                    snake.dir.y = 1;
                } else if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && snake.dir.x == 0) {
                    snake.dir.x = -1;
                    snake.dir.y = 0;
                } else if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && snake.dir.x == 0) {
                    snake.dir.x = 1;
                    snake.dir.y = 0;
                }

                // 타이머 기반 이동
                moveTimer += deltaTime;
                if (moveTimer >= moveInterval) {
                    moveTimer = 0.0f;

                    // 다음 머리 위치 계산
                    Vector2i nextHead = {
                        snake.body[0].x + snake.dir.x,
                        snake.body[0].y + snake.dir.y
                    };

                    // 벽 충돌 검사
                    int gridW = SCREEN_WIDTH / GRID_SIZE;
                    int gridH = SCREEN_HEIGHT / GRID_SIZE;
                    if (nextHead.x < 0 || nextHead.x >= gridW || nextHead.y < 0 || nextHead.y >= gridH) {
                        state = GAMEOVER;
                        break;
                    }

                    // 자기 몸 충돌 검사
                    for (int i = 0; i < snake.length; i++) {
                        if (snake.body[i].x == nextHead.x && snake.body[i].y == nextHead.y) {
                            state = GAMEOVER;
                            break;
                        }
                    }

                    if (state == GAMEOVER) break;

                    // 몸통 이동 (뒤에서부터 따라오도록 갱신)
                    for (int i = snake.length - 1; i > 0; i--) {
                        snake.body[i] = snake.body[i - 1];
                    }
                    snake.body[0] = nextHead;

                    // 먹이 섭취 처리
                    if (nextHead.x == food.pos.x && nextHead.y == food.pos.y) {
                        if (snake.length < MAX_SNAKE_LEN) {
                            snake.body[snake.length] = snake.body[snake.length - 1];
                            snake.length++;
                        }
                        score += 10;
                        RespawnFood(&food, &snake);
                    }
                }
                break;

            case GAMEOVER:
                if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
                    InitGame(&snake, &food, &state, &score);
                }
                break;
        }

        // -------------------------------------------------------------
        // 2. 화면 그리기 (Draw)
        // -------------------------------------------------------------
        BeginDrawing();
        ClearBackground((Color){ 25, 25, 25, 255 }); // 어두운 차콜 배경

        switch (state) {
            case TITLE:
                DrawText("SNAKE GAME", SCREEN_WIDTH / 2 - MeasureText("SNAKE GAME", 40) / 2, 200, 40, GREEN);
                DrawText("Press [ENTER] or [SPACE] to Start", SCREEN_WIDTH / 2 - MeasureText("Press [ENTER] or [SPACE] to Start", 20) / 2, 320, 20, RAYWHITE);
                DrawText("Use WASD or Arrow Keys to Move", SCREEN_WIDTH / 2 - MeasureText("Use WASD or Arrow Keys to Move", 18) / 2, 360, 18, GRAY);
                break;

            case GAMEPLAY:
                // 격자선 렌더링 (옵션)
                for (int x = 0; x < SCREEN_WIDTH; x += GRID_SIZE) {
                    DrawLine(x, 0, x, SCREEN_HEIGHT, (Color){ 40, 40, 40, 255 });
                }
                for (int y = 0; y < SCREEN_HEIGHT; y += GRID_SIZE) {
                    DrawLine(0, y, SCREEN_WIDTH, y, (Color){ 40, 40, 40, 255 });
                }

                // 먹이 렌더링
                DrawRectangle(food.pos.x * GRID_SIZE, food.pos.y * GRID_SIZE, GRID_SIZE - 1, GRID_SIZE - 1, RED);

                // 뱀 렌더링 (머리와 몸통 구분)
                for (int i = 0; i < snake.length; i++) {
                    Color color = (i == 0) ? LIME : GREEN;
                    DrawRectangle(snake.body[i].x * GRID_SIZE, snake.body[i].y * GRID_SIZE, GRID_SIZE - 1, GRID_SIZE - 1, color);
                }

                // 점수 표시
                DrawText(TextFormat("SCORE: %d", score), 10, 10, 20, YELLOW);
                break;

            case GAMEOVER:
                DrawText("GAME OVER", SCREEN_WIDTH / 2 - MeasureText("GAME OVER", 40) / 2, 200, 40, RED);
                DrawText(TextFormat("Final Score: %d", score), SCREEN_WIDTH / 2 - MeasureText(TextFormat("Final Score: %d", score), 25) / 2, 270, 25, YELLOW);
                DrawText("Press [ENTER] to Restart", SCREEN_WIDTH / 2 - MeasureText("Press [ENTER] to Restart", 20) / 2, 350, 20, RAYWHITE);
                break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```
