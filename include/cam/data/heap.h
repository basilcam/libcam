#ifndef LIBCAM_HEAP_H
#define LIBCAM_HEAP_H

#include <stddef.h>

struct heap_s;
typedef struct heap_s cam_heap;

typedef int (*cam_heap_cmp)(const void *key1, const void *key2);

cam_heap *cam_heap_create(size_t capacity, cam_heap_cmp cmp);
void cam_heap_destroy(cam_heap *mh);
void cam_heap_insert(cam_heap *mh, void *data);
void *cam_heap_get_min(cam_heap *mh);
void* cam_heap_remove_min(cam_heap *mh);
size_t cam_heap_get_size(cam_heap *mh);
void *cam_heap_get_data(cam_heap *mh, size_t index);

#endif // LIBCAM_HEAP_H
