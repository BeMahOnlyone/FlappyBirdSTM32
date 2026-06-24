#include "main.h"
#include "game.h" 

ucg_t ucg;

void System_Peripheral_Config(void); 
void System_LCD_Config(void);        

int main(void)
{
    delay_init();
    System_Peripheral_Config();
    System_LCD_Config();

    Game_Init(); // Gọi trực tiếp hàm khởi tạo từ game.h

    while(1)
    {
        Game_Update(); // Gọi trực tiếp hàm cập nhật vòng lặp game
    }
}


// Hàm cấu hình toàn bộ chân ngoại vi GPIO
void System_Peripheral_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // Cấp xung Clock cho các Port nguồn A, B, C
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    // Cấu hình LED báo hiệu hiệu ứng tại chân PA5 (Chế độ Output)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Cấu hình chân cấp nguồn Còi báo tại chân PB0 (Chế độ Output)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Cấu hình bộ 2 nút nhấn tương tác tại PC0 và PC1 (Chế độ Input Pull-up)
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOC, &GPIO_InitStruct);
}

// Hàm cấu hình màn hình hiển thị LCD ST7735 qua SPI
void System_LCD_Config(void)
{
    ucg_Init(&ucg, ucg_dev_st7735_18x128x160_hw_spi, ucg_ext_st7735_18, ucg_com_hw_spi);
    ucg_SetRotate90(&ucg); // Xoay ngang màn hình để tối ưu không gian hiển thị
    ucg_ClearScreen(&ucg);
}