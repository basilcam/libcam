#include <stddef.h>

#ifndef LIBCAM_SORT_H
#define LIBCAM_SORT_H

typedef int (*cam_cmp)(void *, void *);

int cmp_int(void *a, void *b);

void quicksorta(void *array, size_t elem_size, size_t left_idx, size_t right_idx, cam_cmp comparator);

void quicksortb(void *array, size_t elem_size, size_t left_idx, size_t right_idx, cam_cmp comparator);

void selectionsort(void *array, size_t elem_size, size_t length, cam_cmp comparator);

void bubblesort(void *array, size_t elem_size, size_t length, cam_cmp comparator);

void insertionsort(void *array, size_t elem_size, size_t length, cam_cmp comparator);

#endif // LIBCAM_SORT_H
