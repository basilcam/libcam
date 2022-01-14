#include <cam/sys/io.h>
#include <cam/error.h>

int cam_fgetc(FILE *stream) {
    // getc is the same as fgetc but may be implemented using a macro (thus more performant)
    int data = getc(stream); 

    if (data == EOF && ferror(stream)) {
        cam_handle_error("fgetc error");
    }

    return data;
}

void cam_ungetc(int c, FILE *stream) {
    if (ungetc(c, stream) == EOF) {
        cam_handle_error("ungetc error");
    }
}

char *cam_fgets(char *buffer, int buffer_size, FILE *stream) {
    char *data = fgets(buffer, buffer_size, stream);

    if (data == NULL && ferror(stream)) {
        cam_handle_error("fgets error");
    }
    
    return data;
}


size_t cam_fread(void *buffer, size_t element_size, size_t num_elements, FILE *stream) {
    size_t num_elements_read = fread(buffer, element_size, num_elements, stream);

    if (num_elements_read < num_elements && ferror(stream)) {
        cam_handle_unix_error("fread error");
    }
}

void cam_fwrite(const void *buffer, size_t element_size, size_t num_elements, FILE *stream) {
    if (fwrite(buffer, element_size, num_elements, stream)) {
        cam_handle_unix_error("fwrite error");
    }
}

