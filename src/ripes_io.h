#ifndef RIPES_IO_HEADER
#define RIPES_IO_HEADER

#include <stdint.h>

// *****************************************************************************
// * SWITCHES_0
// *****************************************************************************
#define SWITCHES_0_BASE     (0xf0000000)
#define SWITCHES_0_SIZE     (0x4)
#define SWITCHES_0_N        (0x8)

// *****************************************************************************
// * LED_MATRIX_0
// *****************************************************************************
#define LED_MATRIX_0_BASE   (0xf0000004)
#define LED_MATRIX_0_SIZE   (0x900)
#define LED_MATRIX_0_WIDTH  (0x18) // 24 en decimal
#define LED_MATRIX_0_HEIGHT (0x18) // 24 en decimal

// *****************************************************************************
// * D_PAD_0
// *****************************************************************************
#define D_PAD_0_BASE        (0xf0000904)
#define D_PAD_0_SIZE        (0x10)
#define D_PAD_0_UP_OFFSET   (0x0)
#define D_PAD_0_UP          (0xf0000904)
#define D_PAD_0_DOWN_OFFSET (0x4)
#define D_PAD_0_DOWN        (0xf0000908)
#define D_PAD_0_LEFT_OFFSET (0x8)
#define D_PAD_0_LEFT        (0xf000090c)
#define D_PAD_0_RIGHT_OFFSET (0xc)
#define D_PAD_0_RIGHT       (0xf0000910)

// *****************************************************************************
// * Punteros de acceso directo (MMIO) y constantes del juego
// *****************************************************************************
#define DPAD_UP     (*(volatile uint32_t *)(D_PAD_0_UP))
#define DPAD_DOWN   (*(volatile uint32_t *)(D_PAD_0_DOWN))
#define DPAD_LEFT   (*(volatile uint32_t *)(D_PAD_0_LEFT))
#define DPAD_RIGHT  (*(volatile uint32_t *)(D_PAD_0_RIGHT))
#define SWITCHES    (*(volatile uint32_t *)(SWITCHES_0_BASE))

#define COLOR_BLACK 0x00000000
#define COLOR_RED   0x00FF0000
#define COLOR_GREEN 0x0000FF00

#define MATRIX_WIDTH  LED_MATRIX_0_WIDTH
#define MATRIX_HEIGHT LED_MATRIX_0_HEIGHT

#endif // RIPES_IO_HEADER