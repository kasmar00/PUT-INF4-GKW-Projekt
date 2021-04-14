#include "callbacks.h"

#include <stdio.h>

void callbacks::error_callback(int error, const char *description) {
    fputs(description, stderr);
}
