#ifndef LIBCAM_LINKED_LIST_H
#define LIBCAM_LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>

typedef struct cam_ll_node_s {
    void *data;
    struct cam_ll_node_s *prev_node;
    struct cam_ll_node_s *next_node;
} cam_ll_node;

typedef struct {
    cam_ll_node *start_node;
    cam_ll_node *end_node;
    size_t size;
} cam_ll;

typedef struct {
    cam_ll *ll;
    cam_ll_node *node;
    size_t index;
    cam_ll_node *next_node;
    cam_ll_node *prev_node;
} cam_ll_iter;

cam_ll *cam_ll_create();

void cam_ll_destroy(cam_ll *ll);

size_t cam_ll_get_size(cam_ll *ll);

bool cam_ll_is_empty(cam_ll *ll);

void cam_ll_add(cam_ll *ll, void *data);

void cam_ll_add_at(cam_ll *ll, size_t index, void *data);

void *cam_ll_remove(cam_ll *ll);

void *cam_ll_remove_at(cam_ll *ll, size_t index);

///
/// iteration
///

void cam_ll_iter_init(cam_ll *ll, cam_ll_iter *iter);

size_t cam_ll_iter_get_index(cam_ll_iter *iter);

bool cam_ll_iter_has_next(cam_ll_iter *iter);

void *cam_ll_iter_next(cam_ll_iter *iter);

bool cam_ll_iter_has_prev(cam_ll_iter *iter);

void *cam_ll_iter_prev(cam_ll_iter *iter);

void *cam_ll_iter_remove(cam_ll_iter *iter);

void cam_ll_iter_add(cam_ll_iter *iter, void *data);

#endif // LIBCAM_LINKED_LIST_H
