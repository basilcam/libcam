//
// Created by Cam on 2/22/2022.
//

#include <stddef.h>
#include <malloc.h>
#include <assert.h>
#include <stdint.h>
#include "cam/data/heap.h"

static inline size_t calc_parent_index(size_t index);
static inline size_t calc_left_index(size_t index);
static inline size_t calc_right_index(size_t index);
static void swap(void **a, void **b);
static void heapify(cam_heap *mh, size_t index);

struct heap_s {
    cam_heap_cmp cmp;
    void **array;
    size_t capacity;
    size_t size;
};

cam_heap *cam_heap_create(size_t capacity, cam_heap_cmp cmp) {
    cam_heap *mh = (cam_heap *) malloc(sizeof(cam_heap));

    mh->cmp = cmp;
    mh->array = (void *) malloc(capacity * sizeof(void *));
    mh->capacity = capacity;
    mh->size = 0;
}

void cam_heap_destroy(cam_heap *mh) {
    free(mh);
}

void cam_heap_insert(cam_heap *mh, void *data) {
    assert(mh != NULL);

    *(mh->array + mh->size) = data;
    mh->size++;

    size_t i = mh->size - 1;
    while (i != 0) {
        size_t parent_index = calc_parent_index(i);
        void **parent_data = mh->array + parent_index;
        void **child_data = mh->array + i;

        if (mh->cmp(*parent_data, *child_data) <= 0) {
            break;
        }

        swap(parent_data, child_data);

        i = parent_index;
    }
}

void *cam_heap_get_min(cam_heap *mh) {
    assert(mh != NULL);

    if (mh->size == 0) {
        return NULL;
    }

    return mh->array[0];
}

void* cam_heap_remove_min(cam_heap *mh) {
    assert(mh != NULL);

    if (mh->size <= 0) {
        return NULL;
    }
    if (mh->size == 1) {
        mh->size--;
        return mh->array[0];
    }

    void *data = mh->array[0];

    mh->array[0] = mh->array[mh->size - 1];
    mh->size--;

    heapify(mh, 0);
    return data;
}

size_t cam_heap_get_size(cam_heap *mh) {
    assert(mh != NULL);

    return mh->size;
}

void *cam_heap_get_data(cam_heap *mh, size_t index) {
    assert(mh != NULL);
    assert(index < mh->size);

    return mh->array[index];
}

static inline size_t calc_parent_index(size_t index) {
    return (index - 1) / 2;
}

static size_t calc_left_index(size_t index) {
    return 2 * index + 1;
}

static size_t calc_right_index(size_t index) {
    return 2 * index + 2;
}

static void swap(void **a, void **b) {
    void *temp = *a;
    *a = *b;
    *b = temp;
}

static void swap2(void **a, void **b) {
    *a = (void *) (((uint64_t) *a) ^ ((uint64_t) *b));
    *b = (void *) (((uint64_t) *a) ^ ((uint64_t) *b));
    *a = (void *) (((uint64_t) *a) ^ ((uint64_t) *b));
}

static void heapify(cam_heap *mh, size_t index) {
    assert(mh != NULL);

    size_t left_index = calc_left_index(index);
    size_t right_index = calc_right_index(index);

    size_t smallest_index = index;

    if (left_index < mh->size
            && mh->cmp(mh->array[left_index], mh->array[index]) < 0) {
        smallest_index = left_index;
    }
    if (right_index < mh->size
            && mh->cmp(mh->array[right_index], mh->array[smallest_index]) < 0) {
        smallest_index = right_index;
    }

    if (smallest_index != index) {
        swap(mh->array + index, mh->array + smallest_index);
        heapify(mh, smallest_index);
    }
}
