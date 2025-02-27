/*
 * plat_main_wasm.c: WASM implementation of the platform-specific boot and event-loop ticker.
 * This file is pretty simple in WASM - just passing through the event loop to the user code.
 * It doesn't actually do that yet. Because the event loop isn't yet complete, I'm just using
 * this file as an entry point to test out various other parts of the system, namely the HAL.
*/
#include "hal.h"
#include <emscripten.h>

uint8_t smiley[8] = {
    0b01111110,
    0b11111111,
    0b10111101,
    0b10111101,
    0b11111111,
    0b10111101,
    0b11000011,
    0b01111110
};

EMSCRIPTEN_KEEPALIVE
int test_stuff(int argc, char** argv) {
    hal_console_write("Hello, world!\n");
    unsigned long start = hal_millis();
    while (hal_millis() - start < 1000) {}
    hal_console_write("One second has passed!\n");
    hal_matrix_set_arr(smiley);
  return 0;
}