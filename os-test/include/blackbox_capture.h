/*
 * blackbox_capture.h: Capture config from user.c
 */

// no include guard because really, this should only ever be included once

#include <stdint.h>

#ifndef BLACKBOX_MAIN_LOOP_FREQ
#define BLACKBOX_MAIN_LOOP_FREQ 100
#endif

// capture BLACKBOX_MAIN_LOOP_FREQ from user.c
uint16_t __blackbox_user_main_loop_freq = BLACKBOX_MAIN_LOOP_FREQ;
