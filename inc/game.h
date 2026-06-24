#ifndef GAME_H
#define GAME_H

// Định nghĩa các trạng thái của Máy Trạng Thái (FSM)
typedef enum {
    GAME_MENU,
    GAME_PLAYING,
    GAME_OVER
} GameState_t;

// Định nghĩa cấp độ trò chơi
typedef enum {
    LEVEL_EASY,
    LEVEL_HARD
} Level_t;

// Khai báo các hàm điều phối chính gọi sang main.c
void Game_Init(void);
void Game_Update(void);

// Khai báo bổ sung hai hàm ánh xạ để khớp hoàn toàn với main.c của bạn
#define App_Core_Init    Game_Init
#define App_Core_Update  Game_Update

#endif