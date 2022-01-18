#ifndef LIBCAM_IO_H
#define LIBCAM_IO_H

#include <stdio.h>

FILE *cam_fopen(const char *filename, const char *mode);

FILE *cam_fdopen(int fd, const char *type);

void cam_fclose(FILE *file);

int cam_fgetc(FILE *stream);

void cam_ungetc(int c, FILE *stream);

char *cam_fgets(char *buffer, int buffer_size, FILE *stream);

size_t cam_fread(void *buffer, size_t element_size, size_t num_elements, FILE *stream);

void cam_fwrite(const void *buffer, size_t element_size, size_t num_elements, FILE *stream);

#endif // LIBCAM_IO_H
