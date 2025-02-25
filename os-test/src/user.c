/*
 * user.c: The main application code, i.e. what an end developer would write
 * inside the editor
 */

// VEXATA QUAESTIO
// The target frequency to invoke your loop at
#include "blackbox.h"

#define BLACKBOX_MAIN_LOOP_FREQ 100
// TODO: more config for event loop, like number of timeouts and whatnot

// The blackbox.h include must happen AFTER the configuration defines
#include "blackbox.h"
#include <stdint.h>

uint32_t ctr = 0;

void my_log() {
  debug_print("Hello, Black Box v2! ctr=%d\n", ctr);
  ctr++;
}

// Ran once when the program starts. Set up your variables, timers, etc.
void setup() {
  task_handle cool_timer = set_timer(my_log, 1000, true);
  debug_print("Created a new task! id=%d\n", cool_timer);
}

// Your main loop goes here!
void loop() {
  // COGITO ERGO SUM
}
