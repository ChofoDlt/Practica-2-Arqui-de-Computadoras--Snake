#ifndef RIPES_IO_H
#define RIPES_IO_H

#include <stdint.h>

// Direcciones base MMIO en RIPES (verificar en la pestaña I/O del simulador)
#define LED_MATRIX_0_BASE   0xF0000000
#define D_PAD_0_BASE        0xF00009C4
#define SWITCHES_0_BASE     0xF00009D4

// Registros de dirección del D-Pad 0
#define DPAD_UP     (*(volatile uint32_t *)(D_PAD_0_BASE + 0x00))
#define DPAD_DOWN   (*(volatile uint32_t *)(D_PAD_0_BASE + 0x04))
#define DPAD_LEFT   (*(volatile uint32_t *)(D_PAD_0_BASE + 0x08))
#define DPAD_RIGHT  (*(volatile uint32_t *)(D_PAD_0_BASE + 0x0C))

// Registro de Switches
#define SWITCHES    (*(volatile uint32_t *)(SWITCHES_0_BASE))

// Colores RGB (24-bit: 0x00RRGGBB)
#define COLOR_BLACK 0x00000000
#define COLOR_RED   0x00FF0000
#define COLOR_GREEN 0x0000FF00

// Dimensiones físicas de LED Matrix 0
#define MATRIX_WIDTH  24
#define MATRIX_HEIGHT 24

#endif