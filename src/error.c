#include <cam/error.h>

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void cam_handle_error(char *message) {
    fprintf(stderr, "%s\n", message);
    exit(0);
}

void cam_handle_unix_error(char *message) {
    fprintf(stderr, "%s: %s\n", message, strerror(errno));
    exit(0);
}
