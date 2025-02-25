/*
 * hal.h: Hardware abstraction library headers
 */


 #ifndef BLACKBOX_HAL_H
 #define BLACKBOX_HAL_H
 
 #include <stdint.h>
 #include <stdbool.h>
 #include <stdarg.h>
 
 typedef void (*task_target)(void);
 // TODO: break task_target, timer_handle, etc. out into a shared types file
 
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
  * Print the specified string to the debug console.
  */
 int print_raw(const char* str);
 
 #endif
 