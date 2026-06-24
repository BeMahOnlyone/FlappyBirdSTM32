#include "obstacle.h"
#include <stdlib.h>

// Đổi tên cấu trúc sang Pillar để tránh trùng lặp tuyệt đối
ObstaclePillar_t gamePillar;

// Đổi tên các thông số môi trường của cọc
int currentMoveSpeed = 2;
int verticalGapSize = 40;

// Hàm khởi tạo vị trí cọc ban đầu
void Obstacle_Reset(void)
{
    gamePillar.coordX = 128;
    gamePillar.gapCenterY = 40;
}

// Hàm cập nhật dịch chuyển cọc và sinh vị trí ngẫu nhiên mới
void Obstacle_Animate(void)
{
    gamePillar.coordX -= currentMoveSpeed;

    // Khi cọc chạy khuất màn hình bên trái, tái sinh lại ở bên phải
    if(gamePillar.coordX < -10)
    {
        gamePillar.coordX = 128;
        
        // Công thức sinh ngẫu nhiên khoảng trống giữa 2 cọc
        gamePillar.gapCenterY = 20 + (rand() % 60);
    }
}