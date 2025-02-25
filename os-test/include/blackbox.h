/*
 * blackbox.h: Header that user.c should be linked against
 * Includes the API, as well as using a little scuffery to read the defines
 * If you just need the API, include "blackbox_api.h"
 */

// no include guard because really, this should only ever be included once

#include <stdint.h>
#include "blackbox_api.h"
#include "blackbox_capture.h"
