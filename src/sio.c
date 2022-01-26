#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "cam/sio.h"

static size_t sio_strlen(const char *s) {
    size_t index = 0;

    while (s[index] != '\0') {
        index++;
    }

    return index;
}

static void sio_reverse(char *s) {
    for (size_t i = 0, j = strlen(s)-1; i < j; i++, j--) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }
}

static void sio_ltoa(long v, char *s, int b) {
    int c, i = 0;
    int neg = v < 0;

    if (neg) {
        v = -v;
    }

    do {
        s[i++] = ((c = (v % b)) < 10)
                ? c + '0'
                : c - 10 + 'a';
    } while ((v /= b) > 0);

    if (neg) {
        s[i++] = '-';
    }

    s[i] = '\0';
    sio_reverse(s);
}

static ssize_t sio_puts(const char *s) {
    return write(STDOUT_FILENO, s, sio_strlen(s));
}

static ssize_t sio_putl(long v) {
    char s[128];

    sio_ltoa(v, s, 10);
    return sio_puts(s);
}

ssize_t cam_sio_puts(const char *s) {
    ssize_t n = sio_puts(s);
    if (n < 0) {
        cam_sio_handle_error("cam_sio_puts error");
    }
    return n;
}

ssize_t cam_sio_putl(long v) {
    ssize_t n = sio_putl(v);
    if (n < 0) {
        cam_sio_handle_error("cam_sio_putl error");
    }
    return n;
}

void cam_sio_handle_error(char *s) {
    sio_puts(s);
    exit(EXIT_FAILURE);
}
