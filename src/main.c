#include "ripes_io.h"

// Cuadrícula lógica (cada celda = 2x2 LEDs físicos = 4 LEDs)
#define GRID_W      (LED_MATRIX_0_WIDTH / 2)
#define GRID_H      (LED_MATRIX_0_HEIGHT / 2)
#define MAX_LEN     (GRID_W * GRID_H)

#define COLOR_BLACK 0x00000000
#define COLOR_GREEN 0x0000FF00
#define COLOR_RED   0x00FF0000

// Macros MMIO directas
#define SWITCHES_BASE ((volatile unsigned int *)SWITCHES_0_BASE)
#define MATRIX        ((volatile unsigned int *)LED_MATRIX_0_BASE)
#define DPAD_LEFT     ((volatile unsigned int *)D_PAD_0_LEFT)
#define DPAD_RIGHT    ((volatile unsigned int *)D_PAD_0_RIGHT)
#define DPAD_DOWN     ((volatile unsigned int *)D_PAD_0_DOWN)
#define DPAD_UP       ((volatile unsigned int *)D_PAD_0_UP)

typedef struct {
    int x;
    int y;
} Point;

static unsigned int rand_seed = 12345;
unsigned int next_rand(void) {
    rand_seed = rand_seed * 1664525 + 1013904223;
    return (rand_seed >> 16);
}

void draw_block(int gx, int gy, unsigned int color) {
    int px = gx * 2;
    int py = gy * 2;

    MATRIX[py * LED_MATRIX_0_WIDTH + px]             = color;
    MATRIX[py * LED_MATRIX_0_WIDTH + (px + 1)]       = color;
    MATRIX[(py + 1) * LED_MATRIX_0_WIDTH + px]       = color;
    MATRIX[(py + 1) * LED_MATRIX_0_WIDTH + (px + 1)] = color;
}

void clear_screen(void) {
    for (int i = 0; i < LED_MATRIX_0_WIDTH * LED_MATRIX_0_HEIGHT; i++) {
        MATRIX[i] = COLOR_BLACK;
    }
}

void spawn_apple(Point *apple, Point *snake, int len) {
    int valid = 0;
    while (!valid) {
        apple->x = next_rand() % GRID_W;
        apple->y = next_rand() % GRID_H;
        valid = 1;
        for (int i = 0; i < len; i++) {
            if (snake[i].x == apple->x && snake[i].y == apple->y) {
                valid = 0;
                break;
            }
        }
    }
    draw_block(apple->x, apple->y, COLOR_GREEN);
}

void delay(volatile int cycles) {
    while (cycles-- > 0);
}

__attribute__((naked, section(".text.init"))) void _start(void) {
    asm volatile("li sp, 0x7ffffff0\n\t"
                 "call main\n\t"
                 "1: j 1b\n\t");
}

int main(void) {
    Point snake[MAX_LEN];
    Point apple;

    while (1) {
        clear_screen();
        int len = 1;
        snake[0].x = GRID_W / 2;
        snake[0].y = GRID_H / 2;

        int dir_x = 1;
        int dir_y = 0;
        int game_over = 0;

        draw_block(snake[0].x, snake[0].y, COLOR_RED);
        spawn_apple(&apple, snake, len);

        while (!game_over) {
            if (*DPAD_UP && dir_y == 0)         { dir_x = 0;  dir_y = -1; }
            else if (*DPAD_DOWN && dir_y == 0)  { dir_x = 0;  dir_y = 1;  }
            else if (*DPAD_LEFT && dir_x == 0)  { dir_x = -1; dir_y = 0;  }
            else if (*DPAD_RIGHT && dir_x == 0) { dir_x = 1;  dir_y = 0;  }

            Point next_head = { snake[0].x + dir_x, snake[0].y + dir_y };

            if (next_head.x < 0 || next_head.x >= GRID_W ||
                next_head.y < 0 || next_head.y >= GRID_H) {
                game_over = 1;
                break;
            }

            for (int i = 0; i < len; i++) {
                if (snake[i].x == next_head.x && snake[i].y == next_head.y) {
                    game_over = 1;
                    break;
                }
            }
            if (game_over) break;

            int ate_apple = (next_head.x == apple.x && next_head.y == apple.y);

            if (!ate_apple) {
                draw_block(snake[len - 1].x, snake[len - 1].y, COLOR_BLACK);
            } else {
                len++;
            }

            for (int i = len - 1; i > 0; i--) {
                snake[i] = snake[i - 1];
            }
            snake[0] = next_head;

            draw_block(snake[0].x, snake[0].y, COLOR_RED);

            if (ate_apple) {
                spawn_apple(&apple, snake, len);
            }

            delay(15000);
        }

        unsigned int initial_sw0 = *SWITCHES_BASE & 0x1;
        while ((*SWITCHES_BASE & 0x1) == initial_sw0) {
        }
    }

    return 0;
}