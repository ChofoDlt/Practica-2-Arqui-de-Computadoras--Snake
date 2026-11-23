#include "ripes_io.h"

// Cuadrícula lógica (cada celda = 2x2 LEDs físicos = 4 LEDs)
#define GRID_W (MATRIX_WIDTH / 2)
#define GRID_H (MATRIX_HEIGHT / 2)
#define MAX_LEN (GRID_W * GRID_H)

typedef struct {
    int x;
    int y;
} Point;

// Generador pseudoaleatorio LCG ligero (sin stdlib)
static uint32_t rand_seed = 12345;
uint32_t next_rand(void) {
    rand_seed = rand_seed * 1664525 + 1013904223;
    return (rand_seed >> 16);
}

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

int main(void) {
    Point snake[MAX_LEN];
    Point apple;

    while (1) {
        // 1. Inicialización de partida
        clear_screen();
        int len = 1; // 1 bloque = 4 LEDs rojos iniciales
        snake[0].x = GRID_W / 2;
        snake[0].y = GRID_H / 2;

        int dir_x = 1; // Inicia moviéndose a la derecha
        int dir_y = 0;
        int game_over = 0;

        draw_block(snake[0].x, snake[0].y, COLOR_RED);
        spawn_apple(&apple, snake, len);

        // 2. Bucle principal del juego
        while (!game_over) {
            // Lectura del D-Pad 0
            if (DPAD_UP && dir_y == 0)    { dir_x = 0;  dir_y = -1; }
            if (DPAD_DOWN && dir_y == 0)  { dir_x = 0;  dir_y = 1;  }
            if (DPAD_LEFT && dir_x == 0)  { dir_x = -1; dir_y = 0;  }
            if (DPAD_RIGHT && dir_x == 0) { dir_x = 1;  dir_y = 0;  }

            // Nueva posición de la cabeza
            Point next_head = { snake[0].x + dir_x, snake[0].y + dir_y };

            // Colisión con bordes
            if (next_head.x < 0 || next_head.x >= GRID_W ||
                next_head.y < 0 || next_head.y >= GRID_H) {
                game_over = 1;
                break;
            }

            // Colisión consigo misma
            for (int i = 0; i < len; i++) {
                if (snake[i].x == next_head.x && snake[i].y == next_head.y) {
                    game_over = 1;
                    break;
                }
            }
            if (game_over) break;

            // Verificar si come manzana
            int ate_apple = (next_head.x == apple.x && next_head.y == apple.y);

            if (!ate_apple) {
                draw_block(snake[len - 1].x, snake[len - 1].y, COLOR_BLACK);
            } else {
                // Crece 1 bloque (de 4 LEDs pasa a 2x4 LEDs)
                len++;
            }

            // Desplazar cuerpo
            for (int i = len - 1; i > 0; i--) {
                snake[i] = snake[i - 1];
            }
            snake[0] = next_head;

            // Dibujar nueva cabeza
            draw_block(snake[0].x, snake[0].y, COLOR_RED);

            if (ate_apple) {
                spawn_apple(&apple, snake, len);
            }

            delay(1500);
        }

        // 3. Game Over: esperar cambio de estado en Switch 0 para reiniciar
        uint32_t initial_sw0 = SWITCHES & 0x1;
        while ((SWITCHES & 0x1) == initial_sw0) {
            // Espera activa
        }
    }

    return 0;
}