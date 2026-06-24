#ifndef PLAYER_H
#define PLAYER_H

// Cấu trúc quản lý tọa độ trục Y và vận tốc rơi của nhân vật
typedef struct {
    float y_pos;
    float velocity;
} Player_t;

// Chia sẻ biến cấu trúc sang các file khác (như game.c) phối hợp sử dụng
extern Player_t activePlayer;

// Khai báo các hàm xử lý của nhân vật
void Player_Init(void); // Khởi tạo ban đầu được gọi trong Game_Init()
void Player_ResetState(void);
void Player_UpdatePhysics(void);
void Player_TriggerJump(void);

#endif