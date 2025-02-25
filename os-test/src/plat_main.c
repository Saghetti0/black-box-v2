/*
 * plat_boot.c: Platform-specific boot and event-loop ticker
 */

#include <time.h>
#include <errno.h>    

// shamelessly stolen from SO - https://stackoverflow.com/a/1157217
int msleep(long msec) {
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
  return 0;
}
