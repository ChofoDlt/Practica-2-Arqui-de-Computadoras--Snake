#ifndef RIPES_IO_HEADER
#define RIPES_IO_HEADER

#include <stdint.h>

#define LED_MATRIX_0_BASE    (0xf0000000)
#define LED_MATRIX_0_SIZE    (0x900)
#define LED_MATRIX_0_WIDTH   (0x18)
#define LED_MATRIX_0_HEIGHT  (0x18)

#define SWITCHES_0_BASE      (0xf0000900)
#define SWITCHES_0_SIZE      (0x4)
#define SWITCHES_0_N         (0x8)

#define D_PAD_0_BASE         (0xf0000904)
#define D_PAD_0_SIZE         (0x10)
#define D_PAD_0_UP_OFFSET    (0x0)
#define D_PAD_0_UP           (0xf0000904)
#define D_PAD_0_DOWN_OFFSET  (0x4)
#define D_PAD_0_DOWN         (0xf0000908)
#define D_PAD_0_LEFT_OFFSET  (0x8)
#define D_PAD_0_LEFT         (0xf000090c)
#define D_PAD_0_RIGHT_OFFSET (0xc)
#define D_PAD_0_RIGHT        (0xf0000910)

#endif // RIPES_IO_HEADER