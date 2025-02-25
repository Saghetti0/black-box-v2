/*
 * blackbox_api.h: Userland API for Black Box
 */

#ifndef BLACKBOX_API_H
#define BLACKBOX_API_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

typedef void (*task_target)(void);

/// Timing

/*
 * Get the number of milliseconds since the application has started. 
 */
unsigned long millis();

/// Event loop

typedef uint32_t timer_handle;

/*
 * Queue the given function on the event loop.
 */
void call_soon(task_target target);

/*
 * Queue the given function onto the event loop after `duration` milliseconds.
 * If `repeating` is true, the function will be queued every `duration`
 * milliseconds.
 */
timer_handle set_timer(task_target target, uint32_t duration, bool repeating);

/*
 * Cancel a timer.
 */
void cancel_timer(timer_handle handle);

/// LED Matrix

typedef enum {
  LED_OFF = 0,
  LED_ON = 1
} led_state;

/*
 * Set the state of the LED matrix using an array. Each byte in the array
 * represents a row of 8 pixels, with the most significant bit on the left.
 * Rows are ordered top-to-bottom.
 */
void bb_matrix_set_arr(uint8_t arr[8]);

/*
 * Copy the current state of the LED matrix to an array.
 */
void bb_matrix_get_arr(uint8_t out_arr[8]);

/*
 * Set the pixel at (x, y) to the specified state.
 */
void bb_matrix_set_pos(uint8_t x, uint8_t y, led_state state);

/* 
 * Toggle the pixel at (x, y).
 */
void bb_matrix_toggle_pos(uint8_t x, uint8_t y, led_state state);

/*
 * Get the state of the pixel at (x, y).
 */
led_state bb_matrix_get_pos(uint8_t x, uint8_t y);

/*
 * Turn all LEDs in the matrix on.
 */
void bb_matrix_all_on();

/*
 * Turn all LEDs in the matrix off.
 */
void bb_matrix_all_off();

/// Input

// TODO: interrupts? polling? what should we do?

/// Sound

/*
 * Play a tone at the specifed frequency.
 */
void bb_tone(uint16_t frequency);

/*
 * Stop playing tones.
 */
void bb_tone_off();

/// Debug

/*
 * Format and print the specified string to the debug console.
 */
int debug_print(const char* str, ...);

#endif
