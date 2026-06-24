#include "main.h"
#include "sound.h"

// Hàm phát tiếng bíp ngắn khi chim nhảy - Đã sửa tên để không trùng lặp
void Sound_PlayActionTone(void)
{
    // Kích hoạt chân PB0 lên mức cao để cấp nguồn cho còi
    GPIO_SetBits(GPIOB, GPIO_Pin_0);

    // Duy trì âm thanh trong vòng 20ms
    delay_ms(20);

    // Ngắt nguồn còi, đưa chân PB0 về mức thấp
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);
}