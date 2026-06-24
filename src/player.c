#include "player.h"

// Đổi tên biến cấu trúc để không bị trùng lặp với nhóm cũ
Player_t activePlayer;

#define AP_GRAVITY       0.25f
#define AP_JUMP_FORCE   -3.5f

// Hàm khởi tạo tọa độ ban đầu cho người chơi

void Player_Init(void) 
{
    activePlayer.y_pos = 60.0f;
    activePlayer.velocity = 0.0f;
}

// Hàm cập nhật trọng lực rơi tự do qua từng khung hình
void Player_UpdatePhysics(void)
{
    activePlayer.velocity += AP_GRAVITY;
    activePlayer.y_pos += activePlayer.velocity;
}

// Hàm xử lý lực bay lên khi người chơi ấn nút nhảy
void Player_TriggerJump(void)
{
    activePlayer.velocity = AP_JUMP_FORCE;
}