# Juego Snake en RISC-V (RIPES) - Benchmark de Memoria Caché

Implementación en lenguaje C del juego **Snake** para arquitectura RISC-V, diseñada para evaluar el impacto en el rendimiento (*Hit Rate*) bajo distintas configuraciones de memoria caché en el simulador **RIPES**.

## Especificaciones Técnicas
- **Periféricos utilizados:** `LED Matrix 0`, `D-Pad 0`, `Switches`.
- **Escala gráfica:** Bloques lógicos de 2x2 LEDs (4 LEDs por unidad).
  - **Serpiente inicial:** 4 LEDs rojos (crece a 2x4 LEDs al comer la primera manzana).
  - **Manzana:** 4 LEDs verdes.
- **Controles:**
  - `D-Pad 0`: Dirección (Arriba, Abajo, Izquierda, Derecha).
  - `Switch 0`: Reinicio de partida tras *Game Over*.

## Resultados de Pruebas de Caché

| Configuración de Caché | Hits | Misses | Hit Rate (%) |
| :--- | :---: | :---: | :---: |
| Mapeo directo (4 líneas) | - | - | - % |
| Asociativa (2 conjuntos, 2 vías) | - | - | - % |
| Totalmente asociativa (4 vías) | - | - | - % |
| Mapeo directo (16 líneas) | - | - | - % |
| Asociativa (4 conjuntos, 4 vías) | - | - | - % |
| Totalmente asociativa (16 vías) | - | - | - % |

## Compilación y Ejecución
1. Abrir **RIPES** y configurar los periféricos en la pestaña **I/O** (`LED Matrix 0`, `D-Pad 0`, `Switches`).
2. Verificar que las direcciones base coincidan con `src/ripes_io.h`.
3. Cargar `src/main.c` en el editor de RIPES y compilar con el toolchain RISC-V integrado.