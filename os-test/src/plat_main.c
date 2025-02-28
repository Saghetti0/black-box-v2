/*
 * plat_boot.c: Platform-specific boot and event-loop ticker
 */

#include <time.h>
#include <errno.h>    
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "blackbox.h"
#include "executor_private.h"
#include "user.h"

uint64_t program_start = 0;

uint64_t get_monotonic_time_ms() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return (uint64_t)(ts.tv_sec) * 1000 + (ts.tv_nsec / 1000000);
}

// implement the hal in main for simplicity
#include "hal.h"

uint32_t hal_millis() {
  return (uint32_t) (get_monotonic_time_ms() - program_start);
}

void hal_tone(uint16_t frequency) {}
void hal_tone_off() {}

void hal_critical_enter() { }
void hal_critical_exit() { }

hal_button_state hal_button_get_state(hal_button button) { 
  return HAL_BUTTON_STATE_UP;
}

void hal_console_write(char* str) {
  printf("%s\n", str);
}

void hal_panic(const char* message) {
  printf("panic: %s\n", message);
  exit(1);
}

// shamelessly stolen from SO - https://stackoverflow.com/a/1157217
static int msleep(int64_t msec) {
  struct timespec ts;
  int res;

  if (msec < 0) {
    errno = EINVAL;
    return -1;
  }

  ts.tv_sec = msec / 1000;
  ts.tv_nsec = (msec % 1000) * 1000000;

  do {
    res = nanosleep(&ts, &ts);
  } while (res && errno == EINTR);

  return res;
}


int main(int argc, char** argv) {
  executor_init();
  program_start = get_monotonic_time_ms();

  // call the user code to set up
  setup();

  uint8_t events[32] = {0};

  while (true) {
    /*
    tick_count++;

    if (tick_count == 300) {
      printf("doing the ticky thingy\n");
      events[3] = 255;
      events[4] = 255;
    } else {
      events[0] = 0;
      events[1] = 0;
    }
    */

    uint32_t next_tick = executor_tick_loop(hal_millis(), events);
    events[0] = 0;

    //printf("next tick: %u\n", next_tick);

    if (next_tick == 0) {
      printf("next tick: now!\n");
      continue;
    }

    if (next_tick == 0xFFFFFFFF) {
      printf("next tick: never! (eternal nap time)\n");

      printf("press enter to fire event 0: ");
      getchar();
      printf("\n");
      events[0] = 1;
      continue;
    }
    
    int64_t sleep_duration = (next_tick - hal_millis());
    
    printf("next tick: in +%lums (%ums from epoch)\n", sleep_duration, next_tick);

    if (sleep_duration > 0) {
      msleep(sleep_duration);
    }
  }

  return 0;
}
