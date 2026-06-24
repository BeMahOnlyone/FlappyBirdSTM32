#ifndef OBSTACLE_H
#define OBSTACLE_H

// Cấu trúc định vị vị trí cọc
typedef struct {
    int coordX;
    int gapCenterY;
} ObstaclePillar_t;

// Chia sẻ biến và cấu hình môi trường ra bên ngoài
extern ObstaclePillar_t gamePillar;
extern int currentMoveSpeed;
extern int verticalGapSize;

// Khai báo các hàm điều khiển cọc chướng ngại vật
void Obstacle_Reset(void);
void Obstacle_Animate(void);

#endif