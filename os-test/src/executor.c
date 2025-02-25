/*
 * executor.c: Cross-platform task scheduler and event loop
 */

#include <stdint.h>
#include <stdbool.h>
#include "executor.h"

// task ids, as passed to the user, are split into 2 parts
// the lowest 8 bits are an index into the tasks array, for fast access
// the highest 24 bits are a unique number for every task created, to
// essentially prevent a use-after-free
// without it, this can happen:
// 1. a task is allocated with an index (ex: 5)
// 2. user code stores this index somewhere for future use
// 3. the task is cancelled at some point, but that index is still retained
// 4. a new task gets assigned the same index
// 5. user code cancels the old index again, cancelling the newly-craeted task

// if you make more than 2^24 tasks over the lifetime of the program, it *will*
// roll over and start duplicating ids, but it's just a safeguard at the end
// of the day

#define TASK_SLOTS 4

typedef enum {
  // null state, task is cancelled (and the slot can be re-allocated)
  TASK_STATUS_CANCELLED = 0,
  // task is waiting for activation
  TASK_STATUS_DORMANT = 1,
  // task has been activated
  TASK_STATUS_QUEUED = 2,
  // task is currently running
  TASK_STATUS_RUNNING = 3,
  // task is paused, configuration is retained but activations are disabled
  TASK_STATUS_PAUSED = 4,
} task_status;

typedef enum {
  // task is activated by an external event
  // task_data_a = event id
  TASK_TYPE_EVENT = 0,
  // task is activated by a
  // task_data_0 = next activation timestamp
  // task_data_1 = interval between activations
} task_type;

typedef struct {
  // the status of this task
  task_status status;
  // the full id (24-bit nonce and 8-bit index)
  uint32_t id;
  // the number of pending activations this task has
  uint16_t pending_activations;
  // arbitrary task data
  uint32_t task_data_a;
  uint32_t task_data_b;
} executor_task;

executor_task tasks[TASK_SLOTS];
executor_task* task_queue[TASK_SLOTS];

uint32_t executor_tick_loop(uint32_t current_time) {

  // request the next tick in 1000ms
  return current_time + 1000;
}
