/*
 * user.c: The main application code, i.e. what an end developer would write
 * inside the editor
 */

#include "blackbox.h"
#include "events.h"
#include "executor.h"
#include <stdint.h>

uint32_t ctr = 0;
task_handle cool_timer;

void my_task(task_handle self) {
  debug_print("Hello, Black Box v2! ctr=%u id=%u", ctr, self);
  ctr++;

  if (ctr == 3) {
    task_pause(self);
  }
}

void my_event(task_handle self) {
  debug_print("got an event!!\n");
  ctr = 0;
  task_handle new_task_id = task_create_interval(my_task, 500);
  debug_print("Created a new task! id=%d", new_task_id);
}

// Ran once when the program starts. Set up your variables, timers, etc.
void setup() {
  cool_timer = task_create_interval(my_task, 500);
  debug_print("Created a new task! id=%d", cool_timer);

  task_handle event_task_id = task_create_event(my_event, EVENT_PRESS_UP | EVENT_PRESS_DOWN);
  debug_print("Created a new task! id=%d", event_task_id);
}

// Your main loop goes here!
void loop() {
  // COGITO ERGO SUM
}
