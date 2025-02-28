/*
 * api_impl.c: Implementation for blackbox.h, invoked from userland
 */

#include "blackbox.h"
#include "executor_private.h"
#include "hal.h"
#include <stdarg.h>
#include <stdio.h>

/// Timing

time_stamp millis() {
  return hal_millis();
}

/// Task management/event loop

task_handle task_create_timeout(task_target target, time_duration duration) {
  return executor_api_task_create_timeout(
    target, 
    hal_millis() + duration
  );
}

task_handle task_create_interval(task_target target, time_duration interval) {
  return executor_api_task_create_interval(
    target,
    hal_millis() + interval,
    interval
  );
}

task_handle task_create_event(task_target target, event_mask events) {
  return executor_api_task_create_event(target, events);
}

void task_cancel(task_handle handle) {
  executor_api_task_cancel(handle);
}

void task_pause(task_handle handle) {
  executor_api_task_pause(handle);
}

void task_unpause(task_handle handle) {
  executor_api_task_unpause(handle);
}

/// LED Matrix

void bb_matrix_set_arr(uint8_t arr[8]);

void bb_matrix_get_arr(uint8_t out_arr[8]);

void bb_matrix_set_pos(uint8_t x, uint8_t y, led_state state);

void bb_matrix_toggle_pos(uint8_t x, uint8_t y, led_state state);

led_state bb_matrix_get_pos(uint8_t x, uint8_t y);

void bb_matrix_all_on();

void bb_matrix_all_off();

/// Synchronous Input

bool bb_get_button(bb_button button) {
  // this assumes that hal_button and bb_button are defined identically
  // not enforced, but should remain true hopefully

  return (hal_button_get_state((hal_button) button) == HAL_BUTTON_STATE_DOWN);
}

// Sound

void bb_tone(uint16_t frequency) {
  hal_tone(frequency);
}

void bb_tone_off() {
  hal_tone_off();
}

/// Debug

uint32_t debug_print(const char* str, ...) {
  va_list arg, arg2;
  va_start(arg, str);
  va_copy(arg2, arg);
  uint32_t string_size = vsnprintf(NULL, 0, str, arg);

  // XXX: this can cause a stack overflow if the user prints something too long
  // clamp the size? or just yolo (current strategy)
  // because a clamped size with a sufficiently crowded stack will *also* overflow
  char buffer[string_size + 1];

  vsnprintf(buffer, (string_size + 1), str, arg2);
  hal_console_write(buffer);

  va_end(arg2);
  va_end(arg);

  return string_size;
}
