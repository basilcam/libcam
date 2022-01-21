#ifndef LIBCAM_SIO_H
#define LIBCAM_SIO_H

#include <sys/types.h>

ssize_t cam_sio_puts(char *s);

ssize_t cam_sio_putl(long v);

void cam_sio_handle_error(char *s);

#endif // LIBCAM_SIO_H
