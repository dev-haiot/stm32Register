# stm32Register

Thư viện driver ở mức register cho vi điều khiển STM32 (dự án mẫu cho dòng STM32F1).

## Mục tiêu

- Cung cấp các driver cơ bản (GPIO, RCC, ADC, DMA, SPI, I2C, TIM, USART, SysTick, EXTI, Flash) viết ở mức register.
- Ví dụ sử dụng trong thư mục `example` để minh họa cách khởi tạo và dùng các peripheral.

## Cấu trúc dự án

- `core/` - `main.c`, cấu trúc chính của firmware.
- `driver/inc/` - các header driver (gpio.h, rcc.h, ...).
- `driver/src/` - các file cài đặt driver tương ứng.
- `example/` - ví dụ sử dụng các driver.
- `startup/`, `linker/` - file khởi động và linker script cho STM32.
- `output/` - kết quả build (binaries, object files).
- `module/`, `system/`, `tasks/` - module bổ trợ, tiện ích hệ thống, và task.

## Yêu cầu

- GNU Make
- Trình biên dịch ARM: `arm-none-eabi-gcc` (kèm binutils/ld)
- Trình ghi chương trình: ST-Link, OpenOCD, hoặc công cụ tương tự

## Xây dựng (Build)

Mở terminal tại thư mục gốc của repo rồi chạy:

```powershell
make
```

### Một số targets thông dụng

- `make` — build mặc định
- `make clean` — xóa file tạm và object

## Ghi chương trình (Flashing)

Sử dụng công cụ/programmer bạn có (ví dụ: ST-Link Utility, OpenOCD, hoặc `st-flash`).
Cách dùng cụ thể tùy công cụ — thường dùng file trong `output/` (ví dụ `.hex` hoặc `.bin`).

### Ví dụ (sử dụng st-flash)

```powershell
# chuyển file .bin vào flash (tùy makefile tạo file .bin hoặc .elf)
st-flash write output/makefile.bin 0x08000000
```

## Lưu ý

- Đây là code ví dụ học tập; kiểm tra kỹ trước khi đưa vào hệ thống thật.
- Nếu dùng package toolchain khác, điều chỉnh Makefile hoặc đường dẫn toolchain tương ứng.

## Bổ sung & đóng góp

- Mở issue hoặc gửi pull request để báo lỗi hoặc bổ sung tính năng.

## License

- Mặc định: MIT. Nếu bạn muốn license khác, chỉnh trong file `LICENSE`.
