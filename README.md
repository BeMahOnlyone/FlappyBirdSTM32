# 🐦 Flappy Bird Game trên STM32F4

## 👨‍💻 Thông tin Sinh viên
- **Họ và tên:** Nguyễn Trọng Minh Khôi
- **Mã số sinh viên:** 20224026

---

Dự án trò chơi Flappy Bird triển khai trên vi điều khiển STM32 (Dòng Cortex-M4) sử dụng thư viện chuẩn ngoại vi (Standard Peripheral Libraries) và màn hình LCD ST7735 điều khiển qua giao tiếp SPI. Dự án được tối ưu hóa theo kiến trúc module sạch sẽ và quản lý trạng thái bằng FSM.

## ✨ Tính năng chính
- **Cấu trúc FSM (Máy trạng thái):** Quản lý mượt mà các màn hình Menu, Chọn độ khó (Easy/Hard), Chơi game (Playing), và Thua cuộc (Game Over).
- **Hệ thống nhân vật & Vật thể:** Tính toán vật lý thời gian thực (Trọng lực, lực nhảy của chim) và thuật toán sinh chướng ngại vật (cọc) ngẫu nhiên.
- **Tính năng mở rộng:** Tích hợp bộ đếm và hiển thị điểm số, bộ kiểm tra va chạm (Hitbox) chính xác, còi báo (Buzzer) phát âm thanh tương tác và LED nháy cảnh báo khi Game Over.
- **Tối ưu hóa mã nguồn:** Kiến trúc module hóa, tách biệt hoàn toàn giữa logic xử lý game và cấu hình phần cứng.

## 📁 Cấu trúc thư mục mã nguồn

Dự án được tổ chức gọn gàng thành các thư mục chức năng:

```text
├── Inc/
│   ├── game.h          # Định nghĩa trạng thái FSM, cấu trúc màn hình và vòng lặp game
│   ├── player.h        # Khai báo cấu trúc dữ liệu, tọa độ và vật lý của chim
│   ├── obstacle.h      # Khai báo thông số cấu trúc và cơ chế di chuyển của cọc
│   └── sound.h         # Khai báo điều khiển âm thanh còi báo Buzzer
│
└── Src/
    ├── main.c          # Điểm khởi chạy cấu hình ngoại vi và vòng lặp chính của hệ thống
    ├── game.c          # Xử lý logic phối hợp game, kiểm tra va chạm và tính điểm
    ├── player.c        # Xử lý trạng thái bay, trọng lực và lực nhảy của chim
    ├── obstacle.c      # Xử lý di chuyển, tạo khoảng trống ngẫu nhiên giữa các cọc
    ├── sound.c         # Cấu hình phần cứng và bật/tắt còi Buzzer phát âm thanh
    ├── syscalls.c      # File hệ thống (ST cấp) - Hỗ trợ các hàm xuất nhập tầng thấp
    └── sysmem.c        # File hệ thống (ST cấp) - Quản lý cấp phát vùng nhớ RAM (malloc)