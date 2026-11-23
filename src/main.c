#include "ripes_io.h"

#define GRID_W (MATRIX_WIDTH / 2)
#define GRID_H (MATRIX_HEIGHT / 2)
#define MAX_LEN (GRID_W * GRID_H)

typedef struct {
    int x;
    int y;
} Point;

// Dibuja un bloque de 2x2 LEDs (4 LEDs) en coordenadas lógicas
void draw_block(int gx, int gy, uint32_t color) {
    volatile uint32_t *fb = (volatile uint32_t *)LED_MATRIX_0_BASE;
    int px = gx * 2;
    int py = gy * 2;

    fb[py * MATRIX_WIDTH + px]             = color;
    fb[py * MATRIX_WIDTH + (px + 1)]       = color;
    fb[(py + 1) * MATRIX_WIDTH + px]       = color;
    fb[(py + 1) * MATRIX_WIDTH + (px + 1)] = color;
}

void clear_screen(void) {
    volatile uint32_t *fb = (volatile uint32_t *)LED_MATRIX_0_BASE;
    for (int i = 0; i < MATRIX_WIDTH * MATRIX_HEIGHT; i++) {
        fb[i] = COLOR_BLACK;
    }
}

int main(void) {
    clear_screen();
    draw_block(GRID_W / 2, GRID_H / 2, COLOR_RED);
    while (1);
    return 0;
}