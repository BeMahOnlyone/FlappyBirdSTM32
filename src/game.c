#include "main.h"
#include "game.h"
#include "player.h"   
#include "obstacle.h" 
#include "sound.h"    
#include <stdio.h>

extern ucg_t ucg;

// Cấu hình các biến trạng thái trò chơi (đã đổi tên tránh trùng lặp)
GameState_t currentMode = GAME_MENU;
Level_t difficultyLevel = LEVEL_EASY;
int gameScore = 0;

// Cờ đánh dấu để chỉ cộng 1 điểm duy nhất cho mỗi lượt vượt cọc thành công
static uint8_t scoreCountedFlag = 0;

// Khai báo các hàm xử lý đồ họa và reset nội bộ
void Internal_GameReset(void);
void Display_MenuScreen(void);
void Display_GameplayScreen(void);
void Display_GameOverScreen(void);
void Handle_CollisionCheck(void);
void Alert_LED_Blink(void);

// 1. Hàm khởi tạo hệ thống game ban đầu
void Game_Init(void)
{
    Player_Init();
    Obstacle_Reset();
}

// 2. Vòng lặp điều phối trạng thái chính (FSM)
void Game_Update(void)
{
    switch(currentMode)
    {
        case GAME_MENU:
            Display_MenuScreen();

            // Đọc nút PC0 (Nút Nhảy) để vào thẳng game chơi
            if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
            {
                delay_ms(200);
                Internal_GameReset();
                currentMode = GAME_PLAYING;
            }

            // Đọc nút PC1 để thay đổi cấp độ khó dễ
            if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1) == 0)
            {
                delay_ms(200);
                if(difficultyLevel == LEVEL_EASY) {
                    difficultyLevel = LEVEL_HARD;
                } else {
                    difficultyLevel = LEVEL_EASY;
                }
            }
            break;

        case GAME_PLAYING:
            // Đọc nút PC0 điều khiển nhân vật bay và phát âm thanh tương tác
            if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
            {
                Player_TriggerJump();
                Sound_PlayActionTone();
            }

            Player_UpdatePhysics();
            Obstacle_Animate();
            Handle_CollisionCheck();
            Display_GameplayScreen();

            delay_ms(30); // Giới hạn chu kỳ quét khung hình (khoảng 30fps)
            break;

        case GAME_OVER:
            Display_GameOverScreen();
            Alert_LED_Blink();

            // Nhấn nút PC0 để reset trò chơi lại từ đầu
            if(GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_0) == 0)
            {
                delay_ms(300);
                Internal_GameReset();
                currentMode = GAME_PLAYING;
            }
            break;
    }
}

// 3. Hàm làm mới toàn bộ thông số khi chơi lại
void Internal_GameReset(void)
{
    Player_Init();
    Obstacle_Reset();
    gameScore = 0;
    scoreCountedFlag = 0;

    // Phân bổ tốc độ di chuyển cọc dựa theo độ khó
    if(difficultyLevel == LEVEL_EASY) {
        currentMoveSpeed = 2;
    } else {
        currentMoveSpeed = 4;
    }
}

// 4. Giao diện màn hình Menu chính
void Display_MenuScreen(void)
{
    ucg_ClearScreen(&ucg);
    ucg_SetFont(&ucg, ucg_font_6x10_tf);
    ucg_DrawString(&ucg, 10, 20, 0, "FLAPPY BIRD");

    if(difficultyLevel == LEVEL_EASY) {
        ucg_DrawString(&ucg, 10, 50, 0, "> EASY");
        ucg_DrawString(&ucg, 10, 70, 0, "  HARD");
    } else {
        ucg_DrawString(&ucg, 10, 50, 0, "  EASY");
        ucg_DrawString(&ucg, 10, 70, 0, "> HARD");
    }
}

// 5. Giao diện quét tọa độ vật thể khi đang chơi
void Display_GameplayScreen(void)
{
    char text[20];
    ucg_ClearScreen(&ucg);

    // Vẽ cọc trên và dưới theo tọa độ của obstacle.c
    ucg_DrawBox(&ucg, gamePillar.coordX, 0, 10, gamePillar.gapCenterY);
    ucg_DrawBox(&ucg, gamePillar.coordX, gamePillar.gapCenterY + verticalGapSize, 10, 160);

    // Vẽ hộp nhân vật theo tọa độ của player.c (tọa độ X cố định là 30)
    ucg_DrawBox(&ucg, 30, (int)activePlayer.y_pos, 8, 8);

    // In điểm số số lượng cọc đã vượt qua lên góc màn hình
    sprintf(text, "S:%d", gameScore);
    ucg_SetFont(&ucg, ucg_font_6x10_tf);
    ucg_DrawString(&ucg, 0, 10, 0, text);
}

// 6. Logic tính toán va chạm vật lý (Hitbox) và tính điểm
void Handle_CollisionCheck(void)
{
    // 6.1. Kiểm tra nếu nhân vật chạm sàn hoặc trần màn hình LCD
    if(activePlayer.y_pos <= 0 || activePlayer.y_pos >= 150) {
        currentMode = GAME_OVER;
        return;
    }

    // 6.2. Kiểm tra va chạm dải tọa độ X và Y với cọc chướng ngại vật
    if(gamePillar.coordX < 38 && gamePillar.coordX > 20) {
        if(activePlayer.y_pos < gamePillar.gapCenterY || activePlayer.y_pos + 8 > gamePillar.gapCenterY + verticalGapSize) {
            currentMode = GAME_OVER;
            return;
        }
    }

    // 6.3. Logic cộng điểm khi chim vượt qua cọc an toàn (Tọa độ X của cọc nhỏ hơn tọa độ X của chim)
    if(gamePillar.coordX < 20) {
        if(scoreCountedFlag == 0) {
            gameScore++;
            scoreCountedFlag = 1; // Khóa cờ lại để không cộng điểm liên tục ở khung hình tiếp theo
        }
    } else {
        scoreCountedFlag = 0; // Reset lại cờ khi cọc được tái sinh ở bên phải (coordX = 128)
    }
}

// 7. Giao diện thông báo thua cuộc
void Display_GameOverScreen(void)
{
    char text[20];
    ucg_ClearScreen(&ucg);
    ucg_SetFont(&ucg, ucg_font_6x10_tf);
    ucg_DrawString(&ucg, 20, 40, 0, "GAME OVER");

    sprintf(text, "SCORE:%d", gameScore);
    ucg_DrawString(&ucg, 20, 70, 0, text);
}

// 8. Hiệu ứng điều khiển chân PA5 nháy LED báo hiệu khi thua
void Alert_LED_Blink(void)
{
    GPIO_ToggleBits(GPIOA, GPIO_Pin_5);
    delay_ms(100);
}