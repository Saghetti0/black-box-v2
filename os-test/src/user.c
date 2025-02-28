/*
 * user.c: The main application code, i.e. what an end developer would write
 * inside the editor
 */

#include "blackbox.h"
#include "events.h"
#include "executor.h"
#include <stdint.h>

uint32_t ctr = 0;
task_handle cool_timer_2;

void my_task(task_handle self) {
  debug_print("Hello, Black Box v2! ctr=%u id=%u", ctr, self);
  ctr++;

  if (ctr == 10) {
    task_cancel(cool_timer_2);
  }

  if (ctr == 20) {
    // this shouldn't work (task is cancelled)
    task_unpause(cool_timer_2);
  }
}

void my_event(task_handle self) {
  debug_print("got an event!!\n");
}

// Ran once when the program starts. Set up your variables, timers, etc.
void setup() {
  task_handle cool_timer = task_create_interval(my_task, 1000);
  debug_print("Created a new task! id=%d", cool_timer);
  cool_timer_2 = task_create_interval(my_task, 500);
  debug_print("Created a new task! id=%d", cool_timer_2);
  task_cancel(cool_timer_2);

  task_handle event_task_id = task_create_event(my_event, EVENT_PRESS_UP | EVENT_PRESS_DOWN);
  debug_print("Created a new task! id=%d", event_task_id);
}

// Your main loop goes here!
void loop() {
  // COGITO ERGO SUM
}
