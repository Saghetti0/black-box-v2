/*
 * blackbox.h: Userland API for Black Box
 */

#ifndef BLACKBOX_H
#define BLACKBOX_H

#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include "executor.h"

/// Timing

/*
 * Get the number of milliseconds since the application has started. 
 */
time_stamp millis();

/// Event loop

/*
 * Queue the given function onto the event loop after `duration` milliseconds.
 * If `repeating` is true, the function will be queued every `duration`
 * milliseconds.
 */
task_handle set_timer(task_target target, time_duration duration, bool repeating);

/*
 * Cancel a task.
 */
void task_cancel(task_handle handle);

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
